#pragma once

#include <Arduino.h>

#define _DEB_BTN_TIME 100

class Button
{
public:
	Button(const byte &pin, const byte &prd);

	bool isPressed();

private:
	const byte _pin;//, _prd;
	bool _flag;
	uint32_t _timer;
};