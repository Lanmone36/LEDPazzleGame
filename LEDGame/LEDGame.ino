#include "./libraries/Button/Button.cpp"
#include "./libraries/LED/LED.cpp"
#include "_texts.h"
#include <LiquidCrystal_I2C.h>

#define _BASIC_LED_BLINK_TIME 500 //Переопределение для более удобного обращения
#define LED_BLINK_DELAY_TIME 500 //Задержка после мигания светодиодом

#define LED_BTN_COUNT 3 //Количество светодиодов
#define MAX_LEVEL 256//Максимальное количество уровней
#define MODES_COUNT 3 //Количество уровней
#define MIDDLE_BUTTON_IND LED_BTN_COUNT/2 //Средняя кнопка

//Пины светодиодов
#define RED_LED A2
#define YELLOW_LED A1
#define GREEN_LED 13

//Пины кнопок
#define RED_BTN 6
#define YELLOW_BTN 9
#define GREEN_BTN 12

#define NONE_LED_BTN 255  //Любое положительное число, кроме пинов под светодиоды и кнопоки

//Параметры дисплея
#define LCD_COLS 16
#define LCD_ROWS 2
#define LCD_ADDR 0x27

Button btns[LED_BTN_COUNT] = {RED_BTN, YELLOW_BTN, GREEN_BTN};
LED leds[LED_BTN_COUNT] = {RED_LED, YELLOW_LED, GREEN_LED};

//LCDManager lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);
LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);
Timer lcd_clear_tmr(750); //Нужен для плавного очищения всего экрана через определённое время

//Структура для хранения пользовательской информации
struct UserData
{
  uint16_t best_scores[MODES_COUNT]{0}; //массив для хранения лучших результатов в режимах
  bool sound : 1; //Флаг для включения/выключения игровых звуков
  bool _is_game: 1;
} User;


//Перечисление для хранения состояния всей игры
enum GameStates
{
  //### Игровые моды(должны стоять первыми и нумероваться от нуля) ###
  _game_mode1,
  _game_mode2,
  _game_mode3,
  //######
  
  //### Меню ###
  _menu_mode1,
  _menu_mode2,
  _menu_mode3,
  _menu_sound //Вкл./Выкл. звук
  //######
} State, LastState;

void leds_update() {
  for (byte _led_ind = 0; _led_ind < LED_BTN_COUNT; _led_ind++)
  {
    leds[_led_ind].update();
  }
}

void lcd_update()
{
  if (lcd_clear_tmr.ready())
  {
    lcd.clear();
    lcd_clear_tmr.stop();
  }
}

void setup() {
  Serial.begin(9600);
  
  lcd.init();
  lcd.backlight();

  State = _menu_mode1;
  LastState = _menu_sound; //Или любое другое состояние, кроме State
}

void loop() {
  leds_update();
  lcd_update();
  
  switch (State)
  {
    case _game_mode1: game_mode1(); break;
    case _game_mode2: game_mode2(); break;
    case _game_mode3: game_mode3(); break;
    case _menu_mode1:
        if (LastState != State)
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(_b_score);
            lcd.print(User.best_scores[0]);
            lcd.setCursor(0, 1);
            lcd.print(menu[0]);

            LastState = State;
        }

         #if (LED_BTN_COUNT%2) //Если кнопок нечётное количество
         if (btns[MIDDLE_BUTTON_IND].isClicked()) //Средняя кнопка
         {
            State = _game_mode1;
            User._is_game = true;
         }
         #else
         if (btns[MIDDLE_BUTTON_IND].isClicked() || btns[MIDDLE_BUTTON_IND+1].isClicked()) //Средняя кнопка
         {
            State = _game_mode1;
            User._is_game = true;
         }
         #endif

        break;
    case _menu_mode2:
        if (LastState != State)
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(_b_score);
            lcd.print(User.best_scores[1]);
            lcd.setCursor(0, 1);
            lcd.print(menu[1]);

            LastState = State;
        }

        break;
    case _menu_mode3:
        if (LastState != State)
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(_b_score);
            lcd.print(User.best_scores[2]);
            lcd.setCursor(0, 1);
            lcd.print(menu[2]);

            LastState = State;
        }

        break;
    case _menu_sound:
        if (LastState != State)
        {
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print(menu[3]);
            lcd.print(User.sound? "ON": "OFF");

            LastState = State;
        }

        break;
  }

  if (!User._is_game)
  {
    if (btns[0].isClicked()) //Первая кнопка
    {
      State = State - 1;
      if (_menu_mode1 > State) {State = _menu_sound;}
    }
    else if (btns[LED_BTN_COUNT-1].isClicked()) //Последняя кнопка
    {
      State = State + 1;
      if (_menu_sound < State) {State = _menu_mode1;}
    }
  }
}
