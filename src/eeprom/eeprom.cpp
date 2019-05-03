#include "eeprom.h"
#include <iostream>
#include "mbed.h"

using namespace std;
EEPROM::EEPROM(I2C * i2c){
    this->i2c = i2c;
    this->i2cAddress = 0xA0; //slave address
}
//this method will be used to get the addons of the dongles
void EEPROM::get_id(char * id, unsigned int aantal){
    char buffer[2] = {0x00, 0x00};
    if (i2c->write(i2cAddress, buffer, 2, 0)) {
        cout << "Failed to read dongle " << endl;
    }
    wait_ms(100);
    if (i2c->read(i2cAddress, id, aantal, 0)){
        cout << "Failed to read dongle " << endl;
    }
}