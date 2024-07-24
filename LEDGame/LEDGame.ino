#include "./libraries/Button/Button.cpp"
#include "./libraries/LED/LED.cpp"
#include "_texts.h"
#include <LiquidCrystal_I2C.h>

#define _BASIC_LED_BLINK_TIME 500 //Переопределение для более удобного обращения
#define LED_BLINK_DELAY_TIME 500 //Задержка после мигания светодиодом

#define LED_BTN_COUNT 3 //Количество светодиодов
#define MIDDLE_BUTTON_IND LED_BTN_COUNT/2 //Индекс средней кнопки
#define MAX_LEVEL 256//Максимальное количество уровней
#define MODES_COUNT 3 //Количество уровней

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

#define LCD_CLEAR_TIME 750 //Время, после которого диспелей очищается
#define LCD_DELAY_TIME 610//Время задержки какого-либо кода после вывода текста на дисплей

#define BACK_DELAY_TIME 1500 //Время задержки перед возвращением в меню

#define  RANDOM_MAX_SEED 10000 //Максимальное значекние выбора "зерна" для рандомной последовательности мигания светодиодов

Button btns[LED_BTN_COUNT] = {RED_BTN, YELLOW_BTN, GREEN_BTN};
LED leds[LED_BTN_COUNT] = {RED_LED, YELLOW_LED, GREEN_LED};

LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);
Timer lcd_clear_tmr(LCD_CLEAR_TIME); //Нужен для очищения всего экрана через определённое время

//Структура для хранения пользовательской информации
struct UserData
{
  uint16_t b_scores[MODES_COUNT]{0}; //массив для хранения лучших результатов в режимах
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
  _menu_sound, //Вкл./Выкл. звук
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

    lcd_clear_tmr.setPeriod(LCD_CLEAR_TIME); //Если вдруг период был изменён
  }
}

void setup() {
  Serial.begin(9600);
  
  lcd.init();
  lcd.backlight();

  State = _menu_mode1;
  LastState = _menu_sound; //Или любое другое состояние, кроме состояния State

  randomSeed(random(0, RANDOM_MAX_SEED));
}

void loop() {
  leds_update();
  lcd_update();

  switch (State)
  {
    case _game_mode1: game_mode1(); break;
    case _game_mode2: game_mode2(); break;
    case _game_mode3: game_mode3(); break;
    #if (LED_BTN_COUNT%2) //Если кнопок нечётное количество
    case _menu_mode1:
        if (LastState != State)
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(_b_score);
            lcd.print(User.b_scores[0]);
            lcd.setCursor(0, 1);
            lcd.print(menu[0]);

            LastState = State;
        }

         if (btns[MIDDLE_BUTTON_IND].isClicked()) //Средняя кнопка
         {
            State = LastState = _game_mode1;
            User._is_game = true;

            randomSeed(random(0, RANDOM_MAX_SEED));

            lcd.clear();
         }
         
        break;
    case _menu_mode2:
        if (LastState != State)
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(_b_score);
            lcd.print(User.b_scores[1]);
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
            lcd.print(User.b_scores[2]);
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
    #else
    case _menu_mode1:
        if (LastState != State)
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(_b_score);
            lcd.print(User.b_scores[0]);
            lcd.setCursor(0, 1);
            lcd.print(menu[0]);

            LastState = State;
        }

         if (btns[MIDDLE_BUTTON_IND].isClicked() || btns[MIDDLE_BUTTON_IND+1].isClicked()) //Средние кнопки
         {
            State = LastState = _game_mode1;
            User._is_game = true;

            lcd.clear();
         }
         
        break;
    case _menu_mode2:
        if (LastState != State)
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(_b_score);
            lcd.print(User.b_scores[1]);
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
            lcd.print(User.b_scores[2]);
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
    #endif
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
