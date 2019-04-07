#include "ButtonManager.h"

ButtonManager::ButtonManager(I2C* i2c, PCA9548* i2c_switch) :
  directions(i2c), actions(i2c), actions_interrupt(actions_interrupt_pin), directions_interrupt(directions_interrupt_pin)
{
  this->i2c_switch = i2c_switch;
  selectActions();
  printf("Directions chip id: %X\r\n", directions.get_chip_id());

  selectDirections();
  printf("Actions    chip id: %X\r\n", actions.get_chip_id());

  keys_changed = false;
  actions_interrupt.fall(mbed::callback(this, &ButtonManager::handleActionInterrupt));
  actions_interrupt.rise(mbed::callback(this, &ButtonManager::handleActionInterrupt));
  directions_interrupt.fall(mbed::callback(this, &ButtonManager::handleDirectionInterrupt));
  directions_interrupt.rise(mbed::callback(this, &ButtonManager::handleDirectionInterrupt));
}

void ButtonManager::selectActions()
{
  i2c_switch->select(1);
}

void ButtonManager::selectDirections()
{
  i2c_switch->select(2);
}

void ButtonManager::handleActionInterrupt()
{
  keys_changed = true;
}

void ButtonManager::handleDirectionInterrupt()
{
  keys_changed = true;
}


int ButtonManager::getDirectionKeysStatus()
{
  selectDirections();
  return directions.get_pressed_key();
}

int ButtonManager::getActionKeysStatus()
{
  selectActions();
  return actions.get_pressed_key();
}

int ButtonManager::getButtonsStatus()
{
  keys_status = getDirectionKeysStatus() + (getActionKeysStatus() << 5);
  return keys_status;
}