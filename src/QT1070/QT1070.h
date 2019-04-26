#pragma once
#include <iostream>
#include "mbed.h"
using namespace std;
class QT1070{
         
    public:
        QT1070(I2C * i2c);
        char get_chip_id();
        void get_pressed_key(char * val);
        char get_pressed_key();
        void calibrate();
    private:
        void write_register(char reg, char value);
        char read_register(char reg);

    private:
        //int i2cfile; //geen default constructor
        I2C * i2c;
        static const int i2cAddress = 0x1B<<1;
};