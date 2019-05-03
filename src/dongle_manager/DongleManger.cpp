#include "DongleManager.h"


DongleManager::DongleManager(I2C* i2c, PCA9548* i2c_switch)
{
  this->i2c_switch = i2c_switch;
  EEPROM * eeprom = new EEPROM(i2c);
  this->eeprom = eeprom;
}
DongleManager::~DongleManager(){
  delete eeprom;
}

void DongleManager::getDongleId(char* buffer, Dongle dongle)
{
  selectDongle(dongle);
  /*for(int i = 0;i < DONGLE_ID_SIZE; i++) {
    buffer[i] = rand();       // fake dongle id with random values
  }*/
  eeprom->get_id(buffer, 8);
}

void DongleManager::selectDongle(Dongle dongle)
{
  printf("Selecting dongle %d\r\n", (int)dongle);
  i2c_switch->select((int) dongle);
}