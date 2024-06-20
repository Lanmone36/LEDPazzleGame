#include "LEDManager.h"

LEDManager::LEDManager(const byte* led_pins, const size_t& size)
{
	this->_len = size;
	this->_leds = new led_data[this->_len];

	for (size_t _led_ind = 0; _led_ind < this->_len; _led_ind++)
	{
		this->_leds[_led_ind].pin = led_pins[_led_ind];
		pinMode(this->_leds[_led_ind].pin, OUTPUT);
	}

	this->_tmr = new Timer(_BASIC_LED_BLINK_TIME);

	this->_state = _free;
}

LEDManager::~LEDManager()
{
	delete[] this->_leds;
	delete this->_tmr;
}

void LEDManager::blink(const size_t& led_ind = _NONE_LED, const uint16_t& prd = _BASIC_LED_BLINK_TIME)
{
	if (this->_state != _blink)
	{
		this->_state = _blink;
		this->led_ind = led_ind;
		this->prd = prd;
	}
}

void LEDManager::setState(const size_t& led_ind = _NONE_LED, const bool& state = LOW)
{
	if (this->_state != _setState)
	{
		this->_state = _setState;
		this->led_ind = led_ind;
		this->_cur_state = state;
	}
}

void LEDManager::update()
{
	if (this->_state == _blink)
	{
		if (this->_tmr->isStop()) //Если до этого светодиоды были в состоянии "ожидания"
		{
			if (this->led_ind == _NONE_LED)
			{
				for (size_t _led_ind = 0; _led_ind < this->_len; _led_ind++)
				{
					digitalWrite(this->_leds[_led_ind].pin, HIGH); //Мигаем всеми светодиодами
					this->_leds[_led_ind].lvl = HIGH;
				}
			}
			else
			{
				digitalWrite(this->_leds[this->led_ind].pin, HIGH); ///Мигаем одним светодиодом
				this->_leds[this->led_ind].lvl = HIGH;
			}

			//Устанавливаем время периода и запускаем таймер
			this->_tmr->setPeriod(prd);
			this->_tmr->start();

			return;
		}

		if (this->_tmr->ready()) //Если период мигания прошёл
		{
			if (this->led_ind == _NONE_LED)
			{
				for (size_t _led_ind = 0; _led_ind < this->_len; _led_ind++)
				{
					digitalWrite(this->_leds[_led_ind].pin, LOW);
					this->_leds[_led_ind].lvl = LOW;
				}
			}
			else
			{
				digitalWrite(this->_leds[this->led_ind].pin, LOW);
				this->_leds[this->led_ind].lvl = LOW;
			}

			this->_tmr->stop();
			this->_state = _free; //"Устанавливаем" светодиоды в режим "ожидания"
		}

		return;
	}

	if (this->_state == _setState)
	{
		if (this->led_ind == _NONE_LED)
		{
			for (size_t _led_ind = 0; _led_ind < this->_len; _led_ind++)
			{
				digitalWrite(this->_leds[_led_ind].pin, this->_cur_state);
				this->_leds[_led_ind].lvl = this->_cur_state;
			}
		}
		
		else
		{
			digitalWrite(this->_leds[this->led_ind].pin, this->_cur_state);
			this->_leds[this->led_ind].lvl = this->_cur_state;
		}

		this->_state = _free;
	}

	return;
}

bool LEDManager::getState(const size_t& led_ind = _NONE_LED)
{
	if (led_ind == _NONE_LED) { return (this->_cur_state || this->_state != _free); }
	if (led_ind < 0 || led_ind >= this->_len) { return false; }
	return (this->_leds[led_ind].lvl);
}