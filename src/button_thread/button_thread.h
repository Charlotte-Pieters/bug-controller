#pragma once
#include "../QT1070/QT1070.h"
#include "../led_manager/LedManager.h"
#include "../PCA9548/PCA9548.h"

class Button_Thread{
    public:
        Button_Thread(QT1070 * qt1070,PCA9548 * i2c_switch, unsigned int i2c_nr, char * value, LedManager::LedNumber lednumber, LedManager * led, Mutex * stdioMutex,Mutex * timerMutex, Timer *t);
    public:
        void run(void);
    private:
        char * key_value;
        PCA9548 * i2c_switch;
        QT1070 * qt1070;
        unsigned int i2c_nr;
        LedManager * led;
        LedManager::LedNumber lednumber;
        Mutex * stdioMutex;
        Mutex * timerMutex;
        Timer *t;
};

