#include "LED.h"

LED::LED(const byte& pin)
{
	this->_pin = pin;
	this->_tmr = new Timer(_BASIC_LED_BLINK_TIME);
	this->_state = _free;
	this->_lvl = false;

	pinMode(pin, OUTPUT);
}

LED::~LED()
{
	delete this->_tmr;
}

void LED::blink(const uint16_t& prd = _BASIC_LED_BLINK_TIME)
{
	if (this->_state != _blink)
	{
		this->_state = _blink;
		this->_prd = prd;
	}
}

void LED::setState(const bool& state = LOW)
{
	if (this->_lvl != state) { this->_lvl = state; }
	this->_state = _setState;
}

void LED::update()
{
	if (this->_state == _blink)
	{
		if (this->_tmr->isStop()) //Если до этого светодиоды были в состоянии "ожидания"
		{
		    digitalWrite(this->_pin, HIGH); ///Мигаем светодиодом
			this->_lvl = HIGH;

			//Устанавливаем время периода и запускаем таймер
			this->_tmr->setPeriod(this->_prd);
			this->_tmr->start();

			return;
		}

		if (this->_tmr->ready()) //Если период мигания прошёл
		{
			digitalWrite(this->_pin, LOW);
			this->_lvl = LOW;

			this->_tmr->stop();
			this->_state = _free; //"Устанавливаем" светодиод в режим "ожидания"
		}

		return;
	}

	if (this->_state == _setState)
	{
		digitalWrite(this->_pin, this->_lvl);
		this->_tmr->stop();

		this->_state = _free;
	}

	return;
}

bool LED::getState()
{
	return this->_lvl;
}