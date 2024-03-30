#include "Button.h"

Button::Button(const byte& pin): _pin(pin)//, _prd(prd)
{
	pinMode(this->_pin, INPUT_PULLUP);
}

bool Button::isPressed()
{
	bool state = digitalRead(this->_pin);

	if (!state){ this->_timer = millis(); }
	if (state && (millis() - this->_timer) >= _DEB_BTN_TIME){ return false; }

	return true;
}