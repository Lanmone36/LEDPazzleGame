#pragma once

#include <Arduino.h>
#include "../Timer/Timer.cpp"

#define _DEB_BTN_TIME 50 //Период времни для "заглушения" дребезга контактов
#define NONE_BTN -1

struct btn_data
{
	btn_data()
	{
		pin = 0;
		state = 1;

		tmr = new Timer(_DEB_BTN_TIME);
	}

	byte pin;
	Timer* tmr; //Массив таймеров для каждой кнопки, чтобы избегать дребезга
	bool state : 1; //Не тратим лишнюю память с помощью битовых полей
};

class ButtonManager
{
public:
	ButtonManager(const byte* btn_pins, const size_t& size);
	~ButtonManager();

	size_t getPressedButton(const size_t& none_btn); //Метод для обработки зажатия кнопки. Возвращает порядковый номер нажатой кнокпи
	size_t getClickedButton(); //Метод для обработки нажатия на кнопку
	size_t size();

private:
	btn_data* _btns = nullptr;

<<<<<<< HEAD
	size_t _len; //������ �������

	void update();
=======
	size_t _len; //Размер массива
>>>>>>> 8953368e4c0ec31518ec08bf0bdc067cadb3616c
};