#pragma once

#include <Arduino.h>
//#include "../Timer/Timer.cpp"

#define NONE_LED -1
#define _BASIC_LED_BLINK_TIME 500

class LEDManager
{
public:
    LEDManager(const byte* led_pins, const size_t& size);
    ~LEDManager();

    void blink(const size_t& led_ind = NONE_LED,
               const uint16_t& prd = _BASIC_LED_BLINK_TIME); //Метод для мигания светодиодом с заданным периодом. Если led_ind = NONE_LED, то мигает всеми светодиодами
private:
    byte* _led_pins = nullptr; //массив пинов светодиодов
    Timer* _tmr = nullptr;

    size_t _len;
};