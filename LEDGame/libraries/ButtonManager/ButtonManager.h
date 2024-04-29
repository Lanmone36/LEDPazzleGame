#pragma once

#include <Arduino.h>
#include "Timer.h"

#define _DEB_BTN_TIME 50 //Период времни для "заглушения" дребезга контактов

class ButtonManager
{
public:
	ButtonManager(const byte* btn_pins);

	byte getPressedButton(); //Метод для обработки зажатия кнопки
	byte getClickedButton(); //Метод для обработки нажатия на кнопку

private:
	const byte* _btn_pins;
	const size_t _len; //Размер массива

	const Timer* _btn_timers;//Массив таймеров для каждой кнопки, чтобы избегать дребезга
};