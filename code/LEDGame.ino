#include "libraries/Button/Button.h"

#define LED_COUNT 3 //Количество светодиодов

//Пины светодиодов
#define RED_LED 13
#define YELLOW_LED 10
#define GREEN_LED 7

//Пины кнопок
#define RED_BUTTON 12
#define YELLOW_BUTTON 9
#define GREEN_BUTTON 6

#define BLINK_TIME 500 //Период мигания светодиодов

#define MAX_LEVEL 10001//Максимальное количество уровней

const byte leds[LED_COUNT] = { RED_LED, YELLOW_LED, GREEN_LED };

Button btns[LED_COUNT] = { RED_BUTTON, YELLOW_BUTTON, GREEN_BUTTON };

byte num_key = 0;
int sum_key = 0, start = 1;
int level = 0;
int levels[101]{};

void setup()
{
    Serial.begin(9600);

    for (int i = 0; i < LED_COUNT; i++)
    {
        pinMode(leds[i], OUTPUT);
    }

    randomSeed(analogRead(A0));
}

void loop()
{
    num_key = get_answer();

    if (num_key != 255)
    {
        sum_key++;

        uint32_t t = millis();
        digitalWrite(leds[num_key], HIGH);
        while (btns[num_key].isPressed()) {};
        digitalWrite(leds[num_key], LOW);

        if (levels[sum_key - 1] != num_key) { level = 0; start = 1; }
        if (!start && level < sum_key) { level++; start = 1; }
    }

    if (start)
    {
        start = 0; sum_key = 0; levels[level] = random(3);

        if (level == 0)
        {
            uint32_t t = millis();
            for (int i = 0; i < LED_COUNT; i++) { digitalWrite(leds[i], HIGH); }
            while (millis() - t < 1000) {};
            for (int i = 0; i < LED_COUNT; i++) { digitalWrite(leds[i], LOW); }
            t = millis();
            while (millis() - t < 500) {};
        }

        for (int i = 0; i <= level; i++) { led_blink(leds[levels[i]]); }
    }
}

//void mode1() //На каждом уровне к последователности добавляется новый цвет
//{
//  byte *levels = new byte[MAX_LEVEL];
//  byte user_ans, state = 0;
//
//  
//}

void led_blink(const byte& pin)
{
    uint32_t timer = millis();

    while ((millis() - timer) < BLINK_TIME) {};
    digitalWrite(pin, HIGH);
    timer = millis();
    while ((millis() - timer) < BLINK_TIME) {};
    digitalWrite(pin, LOW);
}

byte get_answer() //Функция для считывания нажатий пользователя на кнопки
{
    for (int color = 0; color < LED_COUNT; color++)
    {
        if (btns[color].isPressed()) { return color; }
    }

    return 255;
}

void lose()
{
    Serial.println("Sorry, but yoe lost!");
}

void win()
{
    Serial.println("Congratulations, you've won!");
}