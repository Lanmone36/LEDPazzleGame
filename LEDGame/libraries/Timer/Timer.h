#pragma once

#include <Arduino.h>

class Timer
{
public:
	Timer(const uint16_t &prd);

	void start();

	bool ready();
private:
	uint32_t _timer;
	uint16_t _prd;
};