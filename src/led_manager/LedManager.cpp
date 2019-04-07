#include "LedManager.h"


LedManager::LedManager(PinName led1_pin,PinName led2_pin,PinName led3_pin) : 
  led1(led1_pin), led2(led2_pin), led3(led3_pin)
{
  disableAll();
}

void LedManager::setLed(LedNumber number, int state)
{
  switch (number)
  {
    case LED1:
      led1 = state;
      break;
    case LED2:
      led2 = state;
      break;
    case LED3:
      led3 = state;
      break;
  }
}

void LedManager::disable(LedNumber number)
{
  setLed(number, false);
}

void LedManager::enable(LedNumber number)
{
  setLed(number, true);
}

void LedManager::enableAll()
{
  setAll(true);
}

void LedManager::disableAll()
{
  setAll(false);
}

void LedManager::setAll(int value)
{
  led1 = value;
  led2 = value;
  led3 = value;
}

