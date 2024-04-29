#include "ButtonManager.h"

ButtonManager::ButtonManager(const byte* btn_pins) : _btn_pins(pins)
{
	this->_len = sizeof(btn_pins) / sizeof(byte);
	this->_btn_timers = new Timer[this->_len];

	for (byte pin : btn_pins)
	{
		pinMode(pin, INPUT_PULLUP);
		this->_btn_timers
	}
}

byte ButtonManager::getPressedButton()
{
	for (int btn = 0; btn < this->_len; btn++)
	{

	}
	bool state = digitalRead(this->_pin);

	if (!state){ this->_timer = millis(); }
	if (state && (millis() - this->_timer) >= _DEB_BTN_TIME){ return false; }

	return true;
}