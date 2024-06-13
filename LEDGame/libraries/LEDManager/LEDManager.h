#pragma once

#include <Arduino.h>
//#include "../Timer/Timer.cpp"

#define _NONE_LED -1
#define _BASIC_LED_BLINK_TIME 500

enum ledsState
{
    _free,
    _blink,
    _changeState
};

class LEDManager
{
public:
    LEDManager(const byte* led_pins, const size_t& size);
    ~LEDManager();

    void blink(const size_t& led_ind = _NONE_LED,
               const uint16_t& prd = _BASIC_LED_BLINK_TIME); //Метод для мигания светодиодом с заданным периодом. Если led_ind = NONE_LED, то мигает всеми светодиодами
    void changeState(const size_t& led_ind = _NONE_LED); //Изменяет состояния для светодиодов
    void update(); //Обновляет все состояния светодиодов. Нужна конкретно для длительных методов (blink)

    bool getState(const size_t& led_ind); //Возвращает логический уровень (LOW, HIGH) светодиода под индексом led_ind
private:
    byte* _led_pins = nullptr; //массив пинов светодиодов
    Timer* _tmr = nullptr;

    size_t _len;

    ledsState _state;
    size_t led_ind;
    uint16_t prd;

    
};