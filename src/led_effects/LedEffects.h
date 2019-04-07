#pragma once

#include "LedManager.h"

class LedEffects 
{
  public: 
    LedEffects(LedManager* leds);

    void blink(int times = 10, int speed = 5);
    void pingPong(int times = 10, int speed = 5);
  
  private:
    LedManager* leds;
    static const int SPEED_FACTOR = 20;
};