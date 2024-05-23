#include "ButtonManager.h"

ButtonManager::ButtonManager(const byte* btn_pins, const size_t& size)
{
	this->_len = size;
	this->_btns = new btn_data[this->_len]; //��������� ������ � ������

	for (size_t btn_ind = 0; btn_ind < this->_len; btn_ind++)
	{
		this->_btns[btn_ind].pin = btn_pins[btn_ind];

		pinMode(this->_btns[btn_ind].pin, INPUT_PULLUP);
	}
}

ButtonManager::~ButtonManager()
{
	for (size_t btn_ind = 0; btn_ind < this->_len; btn_ind++)
	{
		delete this->_btns[btn_ind].tmr;
	}

	delete[] this->_btns;
}

size_t ButtonManager::getPressedButton(const size_t& none_btn = NONE_BTN)
{
	for (size_t btn_ind = 0; btn_ind < this->_len; btn_ind++)
	{
		bool state = digitalRead(this->_btns[btn_ind].pin);

		if (state == this->_btns[btn_ind].state)
		{
			this->_btns[btn_ind].tmr->start();
		}

		if (this->_btns[btn_ind].tmr->ready()) //���� ��������� ���������
		{
			this->_btns[btn_ind].state = !this->_btns[btn_ind].state;
		}

		if (this->_btns[btn_ind].state == false) //���� ������ ������
		{
			this->_btns[btn_ind].state = !this->_btns[btn_ind].state;
			return btn_ind;
		}
	}

	return none_btn; //���� �� ���� ������ �� ������
}

size_t ButtonManager::size()
{
	return this->_len;
}