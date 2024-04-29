#pragma once

#include <Arduino.h>
#include "Timer.h"

#define _DEB_BTN_TIME 50 //������ ������ ��� "����������" �������� ���������

class ButtonManager
{
public:
	ButtonManager(const byte* btn_pins);

	byte getPressedButton(); //����� ��� ��������� ������� ������
	byte getClickedButton(); //����� ��� ��������� ������� �� ������

private:
	const byte* _btn_pins;
	const size_t _len; //������ �������

	const Timer* _btn_timers;//������ �������� ��� ������ ������, ����� �������� ��������
};