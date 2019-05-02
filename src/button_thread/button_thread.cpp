#include "button_thread.h"

Button_Thread::Button_Thread(QT1070 *qt1070, PCA9548 *i2c_switch, unsigned int i2c_nr, char *value, LedManager::LedNumber lednumber, LedManager *led, Mutex *stdioMutex, Mutex *timerMutex, Timer *t, Timer* t_reset)
{
    this->qt1070 = qt1070;
    this->led = led;
    this->key_value = value;
    this->lednumber = lednumber;
    this->i2c_switch = i2c_switch;
    this->i2c_nr = i2c_nr;
    this->stdioMutex = stdioMutex;
    this->timerMutex = timerMutex;
    this->t = t;
    this->t_reset = t_reset;
}
void Button_Thread::run(void)
{
    char press = 0;
    char *pressed = &press;
    (*key_value) = 0;
    //forever loop
    while (true)
    {
        stdioMutex->lock();
        i2c_switch->select(i2c_nr);
        qt1070->get_pressed_key(pressed);

        if ((*pressed) != 0)
        {
            if (t->read_ms() == 0)
            {
                t->start();
            }
            (*key_value) = (*pressed);
            (*pressed) = 0;
        }
        else{
            t_reset->stop();
            t_reset->reset();
        }
        if ((*key_value) != 0)
        {
            led->enable(lednumber);
        }
        else
        {
            led->disable(lednumber);
        }
        stdioMutex->unlock(); 
    }
}