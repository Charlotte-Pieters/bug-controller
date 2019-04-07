#include "DongleManager.h"


DongleManager::DongleManager(I2C* i2c, PCA9548* i2c_switch)
{
  this->i2c_switch = i2c_switch;
}

void DongleManager::getDongleId(char* buffer, Dongle dongle)
{
  selectDongle(dongle);
  for(int i = 0;i < DONGLE_ID_SIZE; i++) {
    buffer[i] = rand();       // fake dongle id with random values
  }
}

void DongleManager::selectDongle(Dongle dongle)
{
  i2c_switch->select((int) dongle);
}