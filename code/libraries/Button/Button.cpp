#include "Button.h"

Button::Button(const byte& pin, const byte& prd): _pin(pin)//, _prd(prd)
{
	pinMode(this->_pin, INPUT_PULLUP);
}

bool Button::isPressed()
{
	bool state = digitalRead(this->_pin);

	if (!state && !this->_flag && (millis() - this->_timer) >= _DEB_BTN_TIME)
	{
		this->_timer = millis();
		this->_flag = true;

		return true;
	}
	if (state && this->_flag && (millis() - this->_timer) >= _DEB_BTN_TIME)
	{
		this->_timer = millis();
		this->_flag = false;
	}

	return false;
}