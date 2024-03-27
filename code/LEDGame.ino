#include "libraries/Button/Button.h"

#define LED_COUNT 3 //���������� �����������

//���� �����������
#define RED_LED 13
#define YELLOW_LED 10
#define GREEN_LED 7

//���� ������
#define RED_BUTTON 12
#define YELLOW_BUTTON 9
#define GREEN_BUTTON 6

#define BLINK_TIME 500 //������ ������� �����������

#define MAX_LEVEL 100001 //������������ ���������� �������

//enum colors { RED = RED_LED, YELLOW = YELLOW_LED, GREEN = GREEN_LED };
const byte leds = { RED_LED, YELLOW_LED, GREEN_LED };

Button btns[LED_COUNT] = {RED_BUTTON, YELLOW_BUTTON, GREEN_BUTTON};

void setup()
{
	Serial.begin(9600);

	for (int i = 0; i < LED_COUNT; i++)
	{
		pinMode(leds[i], OUTPUT);
	}
}

void loop()
{
	mode1();
}

void mode1() //�� ������ ������ � ����������������� ����������� ����� ����
{
	static byte levels[MAX_LEVEL]{};
	static int state = 0;
	static byte color;

	levels[state] = random(LED_COUNT); //������ ����

	for (int i = 0; i <= state; i++) { led_blink(leds[levels[i]]); }

	int this_level = 0;

	while (this_level <= state)
	{
		color = get_answer();

		if (color == levels[this_level]) { this_level++; }
		else if (color != -1) { break; }
	}

	if (this_level == MAX_LEVEL) { win(); }
	else if (this_level > state) { Serial.println("Perfect!"); } //������� �������
	else { lose(); }
}

void led_blink(const byte& pin)
{
	uint32_t timer = millis();

	digitalWrite(pin, HIGH);
	while ((millis() - timer) < BLINK_TIME) {};
	digitalWrite(pin, LOW);
}

byte get_answer() //������� ��� ���������� ������� ������������ �� ������
{
	for (byte led : leds)
	{
		if (btns[led].isPressed()) { return led; }
	}

	return -1;
}

void lose()
{
	Serial.begin("Sorry, but yoe lost!");
}

void win()
{
	Serial.begin("Congratulations, you've won!");
}