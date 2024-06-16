#include "LEDManager.h"

LEDManager::LEDManager(const byte* led_pins, const size_t& size)
{
	this->_len = size;
	this->_led_pins = new byte[this->_len];

	for (size_t _led_ind = 0; _led_ind < this->_len; _led_ind++)
	{
		this->_led_pins[_led_ind] = led_pins[_led_ind];
		pinMode(this->_led_pins[_led_ind], OUTPUT);
	}

	this->_tmr = new Timer(_BASIC_LED_BLINK_TIME);

	this->_state = _free;
}

LEDManager::~LEDManager()
{
	delete[] this->_led_pins;
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

void LEDManager::changeState(const size_t& led_ind = _NONE_LED)
{
	if (this->_state != _changeState)
	{
		this->_state = _changeState;
		this->led_ind = led_ind;
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
					digitalWrite(this->_led_pins[_led_ind], HIGH); //Мигаем всеми светодиодами
				}
			}
			else
			{
				digitalWrite(this->_led_pins[this->led_ind], HIGH); ///Мигаем одним светодиодом
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
					digitalWrite(this->_led_pins[_led_ind], LOW);
				}
			}
			else
			{
				digitalWrite(this->_led_pins[this->led_ind], LOW);
			}

			this->_tmr->stop();
			this->_state = _free; //"Устанавливаем" светодиоды в режим "ожидания"
		}

		return;
	}

	if (this->_state == _changeState)
	{
		if (this->led_ind == _NONE_LED)
		{
			for (size_t _led_ind = 0; _led_ind < this->_len; _led_ind++)
			{
				digitalWrite(this->_led_pins[_led_ind], !digitalRead(this->_led_pins[_led_ind]));
			}
		}
		
		else
		{
			digitalWrite(this->_led_pins[this->led_ind], !digitalRead(this->_led_pins[this->led_ind]));
		}

		this->_state = _free;
	}

	return;
}

bool LEDManager::getState(const size_t& led_ind)
{
	if (led_ind < 0 || led_ind >= this->_len) { return false; }
	return (this->_state != _free && (led_ind == _NONE_LED || this->led_ind == led_ind));
}