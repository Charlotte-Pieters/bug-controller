#include "LedEffects.h"

LedEffects::LedEffects(LedManager* leds)
{
  this->leds = leds;
}

void LedEffects::blink(int times, int speed)
{
  int delay = SPEED_FACTOR * speed;
  for(int i = 0; i < times; i++){
    leds->enableAll();
    wait_ms(delay);
    leds->disableAll();
    wait_ms(delay);
  }
}

void LedEffects::pingPong(int times, int speed)
{
  int delay = SPEED_FACTOR * speed;
  int led = 0;
  int direction = true;
  for(int i = 0; i < times * 3; i++){
    leds->disableAll();
    switch (led)
    {
      case 1:
        leds->enable(LedManager::LED1);
        break;
      case 2:
        leds->enable(LedManager::LED2);
        break;
      case 3:
        leds->enable(LedManager::LED3);
        break;
    }
    wait_ms(delay);
    if(direction) {
      led++;
    } else {
      led --;
    }
    if(led >= 3 || led <= 0){
      direction = !direction;
    }
  }
  leds->disableAll();
}