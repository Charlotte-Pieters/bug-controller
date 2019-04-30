#include "eeprom.h"
#include <iostream>
#include "mbed.h"

using namespace std;
EEPROM::EEPROM(I2C * i2c){
    this->i2c = i2c;
    this->i2cAddress = 0xA0; //slave address
}
void EEPROM::write_test(){
    char adr[2] = {0x1F,0xE0};
    char test[16] = "123456712391201"; //0x41, 0xE2, 0xC3,0x04,0x01, 0x12, 0x53,0x04,0x01, 0x02, 0x03,0x04,0x01, 0x02, 0x03,'a'
    char buffer[18] = {};
    for(int i = 0; i<18; i++){
        if(i<2){
            buffer[i] = adr[i];
        }
        else{
            buffer[i] = test[i-2];
        }
    }
    if (i2c->write(i2cAddress, buffer, 18, 0) != 18)
    {
        
    }
    else{
        cout << "Failed to set pointer." << endl;
    }
}
//this method will be used to get the addons of the dongles
void EEPROM::get_id(char * id, unsigned int aantal){
    char buffer[2] = {0x00,0x00};
    if (i2c->write(i2cAddress, buffer, 2, 0) != 2)
    {
        
    }
    else{
        cout << "Failed to set pointer." << endl;
    }
    wait(0.5);
    if (i2c->read(i2cAddress, id, aantal, 0) != aantal)
    {
        
    }
    else
    {
        cout << "Failed to read from the i2c device." << endl;  
    }
}
char EEPROM::get_dongle_value(){
    char buffer[2] = {0x00,0xFF};
    char addon;
    if (i2c->write(i2cAddress, buffer, 2, 0) != 2)
    {
        
    }
    else{
        cout << "Failed to set pointer." << endl;
    }
    wait(0.5);
    if (i2c->read(i2cAddress, &addon, 1, 0) != 1)
    {
        
    }
    else
    {
        cout << "Failed to read from the i2c device." << endl;  
    }
    return addon;
}