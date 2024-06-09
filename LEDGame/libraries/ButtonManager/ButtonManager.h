#pragma once

#include <Arduino.h>
#include "../Timer/Timer.cpp"

#define _DEB_BTN_TIME 50 //������ ������ ��� "����������" �������� ���������
#define NONE_BTN -1

struct btn_data
{
	btn_data()
	{
		pin = 0;
		state = 1;

		tmr = new Timer(_DEB_BTN_TIME);
	}

	byte pin;
	Timer* tmr; //������ �������� ��� ������ ������, ����� �������� ��������
	bool state : 1; //�� ������ ������ ������ � ������� ������� �����
};

class ButtonManager
{
public:
	ButtonManager(const byte* btn_pins, const size_t& size);
	~ButtonManager();

	size_t getPressedButton(const size_t& none_btn); //����� ��� ��������� ������� ������. ���������� ���������� ����� ������� ������
	size_t getClickedButton(); //����� ��� ��������� ������� �� ������
	size_t size();

private:
	btn_data* _btns = nullptr;

	size_t _len; //������ �������

	void update();
};