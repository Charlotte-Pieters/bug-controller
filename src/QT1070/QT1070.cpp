#include "QT1070.h"

using namespace std;
QT1070::QT1070(I2C * i2c) {
        this->i2c = i2c;
    }

char QT1070::get_chip_id()
{
    return read_register(0x00);
}
void QT1070::get_pressed_key(char * val)
{
    (*val) = read_register(0x03);
}
char  QT1070::get_pressed_key(){
    return read_register(0x03);
}
void QT1070::calibrate()
{
    write_register(56,0xAA);
}
void QT1070::write_register(char reg, char value){
    char data[] = {reg, value};
    if (i2c->write(i2cAddress, data, 2, 0) != 1)
    {
    
    }
    else
    {
        cout << "Failed to write to the i2c device." << endl;  
    }
}
char QT1070::read_register(char reg){
    char value;
    if (i2c->write(i2cAddress, &reg, 1, 0) != 1)
    {
        
    }
    else{
        cout << "Failed to set pointer." << endl;
    }
    if (i2c->read(i2cAddress, &value, 1, 0) != 1)
    {
    
    }
    else
    {
        cout << "Failed to read from the i2c device." << endl;  
    }
    return value;
}