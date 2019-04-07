#pragma once

#include "mbed.h"

class LedManager {
  public: 
    enum LedNumber {LED1, LED2, LED3};
    LedManager(PinName led1_pin,PinName led2_pin,PinName led3_pin);

    void setLed(LedNumber number, int state);
    void enable(LedNumber number);
    void disable(LedNumber number);

    void setAll(int value);
    void enableAll();
    void disableAll();

  private:
    DigitalOut led1;
    DigitalOut led2;
    DigitalOut led3;
};