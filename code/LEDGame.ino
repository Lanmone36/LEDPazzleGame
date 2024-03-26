#include "libraries/Button/Button.h"

#define LED_COUNT = 3
#define RED_LED = 13
#define YELLOW_LED = 10
#define GREEN_LED = 7

#define BLINK_TIME = 500

#define MAX_LEVEL = 100001

enum colors { RED = RED_LED, YELLOW = YELLOW_LED, GREEN = GREEN_LED };
const byte leds = { RED_LED, YELLOW_LED, GREEN_LED };

Button btns[LED_COUNT];

void setup()
{
	Serial.begin(9600);

	for (int i = 0; i < LED_COUNT; i++)
	{
		pinMode(leds[i], OUTPUT);
		btns[i] = Button(leds[i]);
	}
}

void loop()
{
	mode1();
}

void mode1() //На каждом уровне к последователности добавляется новый цвет
{
	static colors levels[MAX_LEVEL]{};
	static int state = 0;
	static colors color;

	levels[state] = random(GREEN); //Первый цвет

	for (int i = 0; i <= state; i++) { led_blink(leds[levels[i]]); }

	int this_level = 0;

	while (this_level <= state)
	{
		color = get_answer();

		if (color == levels[this_level]) { this_level++; }
		else if (color != -1) { break; }
	}

	if (this_level == MAX_LEVEL) { win(); }
	else if (this_level > state) { Serial.println("Perfect!"); } //Уровень выигран
	else { lose(); }
}

void led_blink(const byte& pin)
{
	uint32_t timer = millis();

	digitalWrite(pin, HIGH);
	while ((millis() - timer) < BLINK_TIME) {};
	digitalWrite(pin, LOW);
}

byte get_answer() //Функция для считывания нажатий пользователя на кнопки
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