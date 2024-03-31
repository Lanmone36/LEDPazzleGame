#include "C:/Users/Nazar/Documents/Arduino/LEDGame/LEDGame/code/libraries/Button/Button.h"
#include "C:/Users/Nazar/Documents/Arduino/LEDGame/LEDGame/code/libraries/Button/Button.cpp"
#include "C:/Users/Nazar/Documents/Arduino/LEDGame/LEDGame/code/libraries/Timer/Timer.h"
#include "C:/Users/Nazar/Documents/Arduino/LEDGame/LEDGame/code/libraries/Timer/Timer.cpp"

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
    mode1();
}

void mode1() //На каждом уровне к последователности добавляется новый цвет
{
    byte levels[MAX_LEVEL];
    byte user_ans;
    int this_level = 0, state = 0;
    bool next_level = true;

    while (state < MAX_LEVEL)
    {
        if (next_level)
        {
            this_level = 0;

            levels[state] = random(LED_COUNT);
            for (int led = 0; led <= state; led++) { led_blink(leds[levels[led]]); }

            next_level = false;
        }

        else
        {
            user_ans = get_answer();

            if (user_ans != 255)
            {
                digitalWrite(leds[user_ans], HIGH);
                while (btns[user_ans].isPressed()) {};
                digitalWrite(leds[user_ans], LOW);

                if (levels[this_level] != user_ans) { break; }
                if (this_level == state) { next_level = true; state++; }

                this_level++;
            }
        }
    }

    if (state == MAX_LEVEL) { win(); }
    else { lose(); }

    // delete[] levels;
}

void led_blink(const byte& pin)
{
    blink_timer.start();
    while (!blink_timer.ready()) {};
    digitalWrite(pin, HIGH);

    blink_timer.start();
    while (!blink_timer.ready()) {};
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
    for (int i = 0; i < LED_COUNT; i++) { digitalWrite(leds[i], HIGH); }
    blink_timer.start();
    while (blink_timer.ready()) {};
    for (int i = 0; i < LED_COUNT; i++) { digitalWrite(leds[i], LOW); }
    blink_timer.start();
    while (blink_timer.ready()) {};
}

void win()
{
    Serial.println("Congratulations, you've won!");
}