#pragma once

#include <Arduino.h>

class Timer
{
public:
	Timer(const uint16_t &prd);

	void start();
	void stop();
	void setPeriod(const uint16_t& prd);

	bool ready();
	bool isStop();
private:
	uint32_t _timer;
	uint16_t _prd;
};