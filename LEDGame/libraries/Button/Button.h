#pragma once

#include <Arduino.h>
#include "../Timer/Timer.cpp"

#define _BASIC_DEB_TIME 50 //Период времни для "заглушения" дребезга контактов

struct States
{
	States()
	{
		_pressed = true;
		_clicked = true;
	}

	bool _pressed : 1;
	bool _clicked : 1;
};

class Button
{
public:
	Button(const byte& pin, const uint16_t& deb_time = _BASIC_DEB_TIME);
	~Button();

	bool isPressed(); //Метод для обработки зажатия кнопки
	bool isClicked(); //Метод для обработки нажатия на кнопку
	void update(); //Общий метод для проверки всех состояний

private:
	byte _pin;
	States _states;

	Timer* _tmr = nullptr;
};