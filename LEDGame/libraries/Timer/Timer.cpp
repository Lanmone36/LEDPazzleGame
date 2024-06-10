#include "Timer.h"

Timer::Timer(const uint16_t &prd)
{
	this->setPeriod(prd);
}

void Timer::start()
{
	this->_timer = millis();
}

void Timer::stop()
{
	this->_timer = 0;
}

void Timer::setPeriod(const uint16_t& prd)
{
	this->_prd = prd;
	this->_timer = 0;
}

bool Timer::ready()
{
	if ((millis() - this->_timer) >= this->_prd)
	{
		this->_timer = millis();
		return true;
	}

	return false;
}

bool Timer::isStop()
{
	return this->_timer == 0;
}