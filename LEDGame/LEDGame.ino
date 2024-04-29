#include <LiquidCrystal_I2C.h>

#include "./libraries/Timer/Timer.cpp"
#include "./libraries/Button/Button.cpp"

#define LED_BTN_COUNT 3 //Количество светодиодов
#define MAX_LEVEL 10001//Максимальное количество уровней

//Пины светодиодов
#define RED_LED 13
#define YELLOW_LED 10
#define GREEN_LED 7

//Пины кнопок
#define RED_BUTTON 12
#define YELLOW_BUTTON 9
#define GREEN_BUTTON 6

#define NONE_LED_BTN 255//Любое число, кроме пинов под светодиоды и кнопоки

//Параметры дисплея
#define LCD_COLS 16
#define LCD_ROWS 2
#define LCD_ADDR 0x27

const byte leds[LED_BTN_COUNT] = { RED_LED, YELLOW_LED, GREEN_LED };

Button btns[LED_BTN_COUNT] = { RED_BUTTON, YELLOW_BUTTON, GREEN_BUTTON };

LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS); //LCD дисплей

void setup()
{
    Serial.begin(9600);

    IOToolsInit();
}

void loop()
{
    mode1();
}
