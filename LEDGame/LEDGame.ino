#include "./libraries/Timer/Timer.h"
#include "./libraries/Button/Button.h"

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

Timer blink_timer(BLINK_TIME); //Таймер для мигания светодиодом

void setup()
{
    Serial.begin(9600);

    for (int i = 0; i < LED_COUNT; i++)
    {
        pinMode(leds[i], OUTPUT);
    }

    randomSeed(analogRead(A3));
}

void loop()
{
    randomSeed(analogRead(A3));
    mode1();
}
