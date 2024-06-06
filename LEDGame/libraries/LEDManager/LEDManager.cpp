#include "LEDManager.h"

LEDManager::LEDManager(const byte* led_pins, const size_t& size)
{
	this->_len = size;
	this->_led_pins = new byte[this->_len];

	for (size_t led_ind = 0; led_ind < this->_len; led_ind++)
	{
		this->_led_pins[led_ind] = led_pins[led_ind];
	}

	this->_tmr = new Timer(_BASIC_LED_BLINK_TIME);
}

LEDManager::~LEDManager()
{
	delete[] this->_led_pins;
	delete this->_tmr;
}

void LEDManager::blink(const size_t& led_ind = NONE_LED, const uint16_t& prd = _BASIC_LED_BLINK_TIME)
{
	if (this->_tmr->isStop()) //Если до этого светодиоды были в состоянии "ожидания"
	{
	    if (led_ind == NONE_LED)
	    {
		    for (size_t led_ind = 0; led_ind < this->_len; led_ind++)
		    {
			    digitalWrite(this->_led_pins[led_ind], HIGH); //Мигаем всеми светодиодами
		    }
	    }
		else
		{
			digitalWrite(this->_led_pins[led_ind], HIGH); ///Мигаем одним светодиодом
		}

		//Устанавливаем время периода и запускаем таймер
		this->_tmr->setPeriod(prd);
		this->_tmr->start();

		return;
	}

	if (this->_tmr->ready()) //Если период мигания прошёл
	{
		if (led_ind == NONE_LED)
	    {
		    for (size_t led_ind = 0; led_ind < this->_len; led_ind++)
		    {
			    digitalWrite(this->_led_pins[led_ind], LOW);
		    }
	    }
		else
		{
			digitalWrite(this->_led_pins[led_ind], LOW);
		}

		this->_tmr->stop(); //"Устанавливаем" светодиоды в режим "ожидания"
	}

	return;
}