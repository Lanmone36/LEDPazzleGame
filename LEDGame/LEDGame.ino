#include "./libraries/ButtonManager/ButtonManager.cpp"
#include "./libraries/LEDManager/LEDManager.cpp"

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

#define NONE_LED_BTN -1//Любое число, кроме пинов под светодиоды и кнопоки

//Параметры дисплея
#define LCD_COLS 16
#define LCD_ROWS 2
#define LCD_ADDR 0x27

byte* btn_init_list = new byte[LED_BTN_COUNT]{RED_BUTTON, YELLOW_BUTTON, GREEN_BUTTON}; //Костыль, но мне нравится
ButtonManager btns(btn_init_list, LED_BTN_COUNT);

byte* led_init_list = new byte[LED_BTN_COUNT]{RED_LED, YELLOW_LED, GREEN_LED}; //Костыль, но мне нравится
LEDManager leds(led_init_list, LED_BTN_COUNT);

void setup()
{
    Serial.begin(9600);

    delete[] btn_init_list; //Освобождаем память
    delete[] led_init_list; //Освобождаем память
}

void loop()
{
  size_t a = btns.getPressedButton();
  if (a != NONE_LED_BTN){Serial.println(a);}

  leds.blink(NONE_LED_BTN, 7500);
}
