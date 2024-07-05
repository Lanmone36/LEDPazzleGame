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
	this->update();

	return !this->_states._pressed; //Так как кнопка "подтянута" к высокому уровню питания, то при нажатии _pressed == false
}

bool Button::isClicked()
{
	this->update();

	return this->_states._clicked;
}

void Button::update()
{
	/*Функция для глобального обновления состояний всех кнопок.
	Вызывается внутри ключевых методов обработки*/

	bool state = digitalRead(this->_pin);

	this->_states._clicked = false;

	if (state == this->_states._pressed)
	{
		this->_tmr->start();
	}

	if (this->_tmr->ready()) //Если произошло изменение cостояния
	{
		this->_states._pressed = !this->_states._pressed;

		if (!state) //Если кнопка нажата
		{
			this->_states._clicked = true;
		}
	}
}