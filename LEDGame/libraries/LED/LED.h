#pragma once

#include <Arduino.h>
//#include "../Timer/Timer.cpp"

#define _BASIC_LED_BLINK_TIME 500

enum State
{
    _free,
    _blink,
    _setState
};

class LED
{
public:
    LED(const byte& pin);
    ~LED();

    void blink(const uint16_t& prd = _BASIC_LED_BLINK_TIME); //Метод для мигания светодиодом с заданным периодом
    void setState(const bool& state = LOW); //метод для изменения логического уровня светодиода
    void update(); //Обновляет все состояния светодиода

    bool getState(); //Возвращает логичсекий уровень (LOW, HIGH) светодиода
private:
    Timer* _tmr = nullptr;
    byte _pin;
    bool _lvl;
    State _state;

    uint16_t _prd;
};