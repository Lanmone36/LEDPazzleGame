#pragma once

#include <Arduino.h>
#include "../Timer/Timer.cpp"

#define _BASIC_DEB_TIME 50 //Период времни для "заглушения" дребезга контактов
#define _BASIC_HOLD_TIME 1000 //Время, через которое кнопка будет считаться зажатой

struct States
{
	States()
	{
		_pressed = true;
		_clicked = false;
		_holded = false;
	}

	bool _pressed : 1;
	bool _clicked : 1;
	bool _holded  : 1;
};

class Button
{
public:
	Button(const byte& pin,
		   const uint16_t& deb_time = _BASIC_DEB_TIME,
		   const uint16_t& hold_time = _BASIC_HOLD_TIME);
	~Button();

	bool isPressed(); //Метод для обработки зажатия кнопки
	bool isClicked(); //Метод для обработки нажатия на кнопку
	bool isHolded(); //Метод для обработки зажатия кнопки

	void setHoldTime(const uint16_t& prd); //Метод для установки времени, через которое
	                                       //кнопка будет считаться зажатой
	void update(); //Общий метод для проверки всех состояний

private:
	byte _pin;

	States _states;

	Timer* _deb_tmr = nullptr;
	Timer* _hold_tmr = nullptr;
};