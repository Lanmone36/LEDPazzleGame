#include "Button.h"

Button::Button(const byte& pin, const uint16_t& deb_time = _BASIC_DEB_TIME)
{
	this->_tmr = new Timer(deb_time);
	this->_pin = pin;

	pinMode(pin, INPUT_PULLUP);
}

Button::~Button()
{
	delete this->_tmr;
}

bool Button::isPressed()
{
	bool state = digitalRead(this->_pin);

	if (state == this->_states._pressed)
	{
		this->_tmr->start();
	}

	if (this->_tmr->ready()) //Если произошло изменение cостояния
	{
		this->_states._pressed = !this->_states._pressed;
	}

	if (!this->_states._pressed) //Если кнопка нажата
	{
		//this->_btns[btn_ind].state = !this->_btns[btn_ind].state;
		return true;
	}

	return false;
}

void Button::update()
{
	/*Функция для глобального обновления состояний всех кнопок.
	Вызывается внутри ключевых методов обработки*/
}