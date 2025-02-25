#include "Timer.h"

Timer::Timer(const uint16_t &prd = 0, const bool& auto_start = false)
{
	this->setPeriod(prd);
	this->_isStop = !auto_start;
}

void Timer::start()
{
	this->_timer = millis();
	this->_isStop = false;
}

void Timer::stop()
{
	this->_isStop = true;
}

void Timer::setPeriod(const uint16_t& prd)
{
	this->_prd = prd;
	this->_timer = millis();
}

bool Timer::ready()
{
	if ((millis() - this->_timer) >= this->_prd && !this->_isStop)
	{
		this->_timer = millis();
		return true;
	}

	return false;
}

bool Timer::isStop()
{
	return this->_isStop;
}