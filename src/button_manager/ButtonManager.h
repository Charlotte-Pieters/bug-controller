#pragma once

#include "mbed.h"
#include "PCA9548.h"
#include "QT1070.h"

class ButtonManager
{
  enum KEYMAP {
    SELECT = 1, LEFT = 2, DOWN = 4, UP = 8, RIGHT = 16,     // keys from left QT1070
    X = 32, A = 64, Y = 128, B = 256, START = 512
  };

  public:
    ButtonManager(I2C* i2c, PCA9548* i2c_switch);

    void addEventListener();
    int getButtonsStatus();

  private:
    PCA9548* i2c_switch;
    QT1070 directions;
    QT1070 actions;
    int keys_status;
    int keys_changed;

    InterruptIn actions_interrupt;
    InterruptIn directions_interrupt;
    static const PinName actions_interrupt_pin = PA_0;
    static const PinName directions_interrupt_pin = PA_1;

    void selectDirections();
    void selectActions();
    void handleDirectionInterrupt();
    void handleActionInterrupt();
    int getDirectionKeysStatus();
    int getActionKeysStatus();
};