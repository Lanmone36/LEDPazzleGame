#include "Button.h"

Button::Button(const byte& pin, const uint16_t& deb_time = _BASIC_DEB_TIME, const uint16_t& hold_time = _BASIC_HOLD_TIME)
{
	this->_deb_tmr = new Timer(deb_time);
	this->_hold_tmr = new Timer(hold_time);
	this->_pin = pin;

	pinMode(pin, INPUT_PULLUP);
}

Button::~Button()
{
	delete this->_deb_tmr;
	delete this->_hold_tmr;
}

bool Button::isPressed()
{
	//this->update();

	return !this->_states._pressed; //Так как кнопка "подтянута" к высокому уровню питания, то при нажатии _pressed == false
}

bool Button::isClicked()
{
	//this->update();

	return this->_states._clicked;
}

bool Button::isHolded()
{
	//this->update();

	return this->_states._holded;
}

void Button::setHoldTime(const uint16_t& prd)
{
	this->_hold_tmr->setPeriod(prd);
}

void Button::update()
{
	/*Функция для глобального обновления состояний всех кнопок.
	Вызывается внутри ключевых методов обработки*/

	bool state = digitalRead(this->_pin);

	if (this->_states._clicked) { this->_states._clicked = false; }

	if (this->_hold_tmr->ready()) 
	{
		this->_hold_tmr->stop();

		this->_states._holded = true;
	}

	if (state == this->_states._pressed)
	{
		this->_deb_tmr->start();
	}

	if (this->_deb_tmr->ready()) //Если произошло изменение cостояния
	{
		this->_states._pressed = !this->_states._pressed;

		if (!state) //Если кнопка нажата
		{
			this->_states._clicked = true;
		}
		else
		{
			this->_states._holded = false;
		}
	}

	if (this->_states._pressed) //Если кнопка не нажата, то "обнуляем" таймер
	{
		this->_hold_tmr->start();
	}
}