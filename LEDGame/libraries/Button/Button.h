#pragma once

#include <Arduino.h>

#define _DEB_BTN_TIME 50

class Button
{
public:
	Button(const byte &pin);

	bool isPressed();

private:
	const byte _pin;//, _prd;
	bool _flag;
	uint32_t _timer;
};