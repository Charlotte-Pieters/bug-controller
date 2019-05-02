#pragma once
#include "mbed.h"
class EEPROM{
    public:
    EEPROM(I2C * i2c);

    public:
    void get_id(char * id, unsigned int aantal);

    private:
    I2C * i2c;
    int i2cAddress; //8-bit address
    
};