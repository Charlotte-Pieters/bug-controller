#include "mbed.h"
#include "Simple-LoRaWAN.h"
#include "settings.h"
#include "LoRaMessage.h"
#include "ButtonManager.h"
#include "PCA9548.h"
#include "LedManager.h"
#include "LedEffects.h"
#include "DongleManager.h"
#include <thread>
#include "button_thread/button_thread.h"
using namespace SimpleLoRaWAN;
using namespace std;
Serial pc(SERIAL_TX, SERIAL_RX, 115200); // tx, rx

LedManager leds(PC_8, PC_9, PC_10);
LedEffects led_effects(&leds);


I2C i2c_bus(PC_1, PC_0);
PCA9548 i2c_switch(i2c_bus);
ButtonManager buttons(&i2c_bus, &i2c_switch);
DongleManager dongles(&i2c_bus, &i2c_switch);

Node node(keys, pins);

static const int DONGLE_ID_SIZE = 8;
static const int DONGLES_COUNT = 4;
char dongles_data[DONGLES_COUNT][DONGLE_ID_SIZE] = {0};

void getAllDongleIds()
{
  dongles.getDongleId(dongles_data[0], DongleManager::DONGLE_1);
  dongles.getDongleId(dongles_data[1], DongleManager::DONGLE_2);
  dongles.getDongleId(dongles_data[2], DongleManager::DONGLE_3);
  dongles.getDongleId(dongles_data[3], DongleManager::DONGLE_4);
}

void sendDongles()
{
  LoRaMessage message;
  for (int dongle = 0; dongle < DONGLES_COUNT; dongle++)
  {
    for (int id_byte = 0; id_byte < DONGLE_ID_SIZE; id_byte++)
    {
      message.addUint8(dongles_data[dongle][id_byte]);
    }
  }
  node.send(message.getMessage(), message.getLength(), 2);
}

int main(void)
{
  pc.printf("*** BUG controller ***\r\n");

  led_effects.blink();
  led_effects.pingPong();

  getAllDongleIds();
  sendDongles();

  led_effects.blink();
  char t1 = 0, t2 = 0;
  QT1070 direction(&i2c_bus);
  QT1070 *direct = &direction;
  char *act_value = &t1;
  char *mov_value = &t2;
  led_effects.blink();
  Mutex m, timerMux;
  Timer t_8, t_reset;
  Button_Thread act(direct, &i2c_switch, 2, act_value, LedManager::LED1, &leds, &m, &timerMux, &t_8, &t_reset);
  Button_Thread mov(direct, &i2c_switch, 1, mov_value, LedManager::LED2, &leds, &m, &timerMux, &t_8, &t_reset);
  Thread actionThread;
  Thread movementThread;
  Thread resetThread;
  actionThread.start(callback(&act, &Button_Thread::run));
  movementThread.start(callback(&mov, &Button_Thread::run));
  while (true)
  {
      if(t_8.read() >= 4){
        m.lock();
        led_effects.pingPong();
        m.unlock();
        LoRaMessage message;
        message.addUint8((*act_value));
        message.addUint8(*mov_value);
        node.send(message.getMessage(), message.getLength(), 2);
        t_8.stop();
        t_8.reset();
        (*act_value) = 0;
        (*mov_value) = 0;
      }
      if((*act_value) == 16 && (*mov_value) == 1 ){
        t_reset.start();
      }
      else if((*act_value) !=16 && (*mov_value) == 1 ){
        (*act_value) = 0;
        (*mov_value) = 0;
        t_8.stop();
        t_8.reset();
      }
      else{
        t_reset.stop();
        t_reset.reset();
      }
      if(t_reset.read() >= 3){
        getAllDongleIds();
        sendDongles();
        led_effects.blink();
        t_reset.stop();
        t_reset.reset();
      }
  }
  printf("*** BUG controller END ***\r\n");
  return 0;
}
