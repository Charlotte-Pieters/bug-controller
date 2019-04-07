# pragma once

#include "PCA9548.h"
#include "eeprom.h"

class DongleManager
{
  public: 
    enum Dongle { DONGLE_1 = 3, DONGLE_2 = 4, DONGLE_3 = 5, DONGLE_4 = 6 };

    DongleManager(I2C* i2c, PCA9548* i2c_switch);

    void getDongleId(char* buffer, Dongle dongle);

  private:
    PCA9548* i2c_switch;

    static const int DONGLE_ID_SIZE = 8;

    void selectDongle(Dongle dongle);
};