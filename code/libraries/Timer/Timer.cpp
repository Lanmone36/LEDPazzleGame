#include <Timer.h>

Timer::Timer(uint16_t prd)
{
	this->_prd = prd;
	this->_timer = 0;
};

void Timer::start()
{
	this->_timer = millis();
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