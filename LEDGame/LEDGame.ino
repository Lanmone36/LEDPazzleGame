#include <LiquidCrystal_I2C.h>

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

const byte leds[LED_COUNT] = { RED_LED, YELLOW_LED, GREEN_LED };

Button btns[LED_COUNT] = { RED_BUTTON, YELLOW_BUTTON, GREEN_BUTTON };

LiquidCrystal_I2C lcd(0x27, 16, 2); //LCD дисплей

void setup()
{
    lcd.init();
    lcd.backlight();

    for (int i = 0; i < LED_COUNT; i++)
    {
        pinMode(leds[i], OUTPUT);
    }
}

void loop()
{
    mode1();
}
