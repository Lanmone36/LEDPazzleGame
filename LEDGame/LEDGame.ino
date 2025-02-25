#include "./libraries/Button/Button.cpp"
#include "./libraries/LED/LED.cpp"
#include "./libraries/PIEZZO/PIEZZO.cpp"
#include "_texts.h"
#include "_sounds.h"

#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

#define _BASIC_LED_BLINK_TIME 500 //Переопределение для более удобного обращения
#define LED_BLINK_DELAY_TIME 500 //Задержка после мигания светодиодом

#define LED_BTN_COUNT 3 //Количество светодиодов (max = 8)
#define MAX_LEVEL 256//Максимальное количество уровней
#define MODES_COUNT 3 //Количество уровней
#define MIDDLE_BUTTON_IND LED_BTN_COUNT/2 //Средняя кнопка

//Пин Пьезо-элемента
#define PZ A1

//Пины светодиодов
#define RED_LED 7
#define YELLOW_LED 10
#define GREEN_LED 11

//Пины кнопок
#define RED_BTN 12
#define YELLOW_BTN 9
#define GREEN_BTN 6

#define NONE_LED_BTN 255  //Любое положительное число, кроме пинов под светодиоды и кнопоки

//Параметры дисплея
#define LCD_COLS 16
#define LCD_ROWS 2
#define LCD_ADDR 0x27

#define lcd_print(pstr) lcd.print((const __FlashStringHelper*)(pstr)) //Макрос для преобразования PROGMEM-строк в тип __FlashStringHelper*
                                                                      //для их правильного чтения и передачи в метод lcd.print()

#define LCD_CLEAR_TIME 750 //Время, после которого диспелей очищается
#define LCD_DELAY_TIME 610//Время задержки какого-либо кода после вывода текста на дисплей

#define BACK_DELAY_TIME 1500 //Время задержки перед возвращением в меню

#define  RANDOM_MAX_SEED 10000 //Максимальное значекние выбора "зерна" для рандомной последовательности мигания светодиодов

Button btns[LED_BTN_COUNT] = {RED_BTN, YELLOW_BTN, GREEN_BTN};
LED leds[LED_BTN_COUNT] = {RED_LED, YELLOW_LED, GREEN_LED};

LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

Piezzo pz(PZ);
bool is_snd_on = false;

Timer lcd_clear_tmr(LCD_CLEAR_TIME); //Нужен для очищения всего экрана через определённое время



#define INIT_EEPROM_ADDR 0 //Адрес памяти, которая будет отвечать за проверку на первую инициализацию
#define INIT_EEPROM_KEY 205 //Ключ проверки на первую инициализацию
#define EEPROM_SIZE EEPROM.length() //Размер EEPROM-памяти
uint16_t data_addr = INIT_EEPROM_ADDR + 1; //Адрес хранения пользовательской информации 
//#define DATA_ADDR INIT_EEPROM_ADDR + 1 //Реализация хранения данных в одной области памяти

//Структура для хранения пользовательской информации в EEPROM-памяти
struct UserData
{
  uint32_t _rewrite_cnt; //Адрес области памяти, в которой будет записана пользовательская информация
  uint16_t b_scores[MODES_COUNT]; //массив для хранения лучших результатов в режимах
  bool sound : 1; //Флаг для включения/выключения игровых звуков
  bool _mem_check : 1; //Флаг для проверки, использовалась ли ранее указанная область памяти
} User;

#define USER_DATA_LENGTH sizeof(User) //Размер пользовательской информации.

bool _is_game = false; //Флаг для контроля игрового процесса

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



//####### IO-функции. Реализация находится в файле _io_tools.ino #######
void leds_btns_update();
void lcd_pz_update();
bool isHoldButton(const byte& btn_ind = NONE_LED_BTN);
byte getPressedButton(bool only_one = true);
byte randomSet(byte count = 1);
void blink(const byte& led_ind = NONE_LED_BTN);
void print_b_score(const byte& game_mode_ind);
void set_sound(Note* snd);
//##############



//####### Реализация изменения области памяти для хранения данных #######
//                          и нахождения её
void set_next_addr() //Меняем адрес записи на следующий
{
  data_addr += USER_DATA_LENGTH;

  if ((data_addr + USER_DATA_LENGTH) > EEPROM_SIZE) {data_addr = 0;} //Начинаем новый цикл
  if (data_addr == INIT_EEPROM_ADDR) {data_addr++;}
}

void get_data() //Находим текущую область памяти с данными
{
  uint32_t _cnt;

  while (true)
  {
    EEPROM.get(data_addr, User);
    _cnt = User._rewrite_cnt;
    
    EEPROM.get(data_addr+USER_DATA_LENGTH, User); //Получаем следущую область памяти хранения пользовательской информации

    if (_cnt > User._rewrite_cnt || User._mem_check) //Если новая область памяти имеет меньшее число перезаписей (текущая область последняя)
                                                     //или ещё не была использована ни разу
    {
      EEPROM.get(data_addr, User); //Оставляем текущую область памяти (так как это последняя перезапись)
      Serial.println(data_addr);

      return;
    }

    set_next_addr();
  }
}

void setup() {
  Serial.begin(9600);
  
  //####### Первая инициализация #######
  if (EEPROM.read(INIT_EEPROM_ADDR) != INIT_EEPROM_KEY)
  {
    for (int i = 0; i<EEPROM_SIZE; i++)
    {
      EEPROM.update(i, 255);
    }
    
    EEPROM.update(INIT_EEPROM_ADDR, INIT_EEPROM_KEY);

    for (byte _ind = 0; _ind < MODES_COUNT; _ind++)
    {
      User.b_scores[_ind] = 0;
    }
    User.sound = false;
    User._mem_check = 0;
    User._rewrite_cnt = 0;
    
    EEPROM.put(data_addr, User);
  }
  //##############
  
  get_data();
  //EEPROM.get(DATA_ADDR, User);
  
  lcd.init();
  lcd.backlight();

  State = _menu_mode1;
  LastState = _menu_sound; //Или любое другое состояние, кроме состояния State

  randomSeed(analogRead(A0));
}

void loop() {
  leds_btns_update();
  lcd_pz_update();

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
            lcd_print(_b_score);
            print_b_score(0);
            lcd.setCursor(0, 1);
            lcd_print(menu[0]);

            LastState = State;
        }

         if (btns[MIDDLE_BUTTON_IND].isClicked()) //Средняя кнопка
         {
           //set_sound(btn_click_snd);
            State = LastState = _game_mode1;
            _is_game = true;

            randomSeed(random(0, RANDOM_MAX_SEED));

            lcd.clear();
         }
         
        break;
    case _menu_mode2:
        if (LastState != State)
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd_print(_b_score);
            print_b_score(1);
            lcd.setCursor(0, 1);
            lcd_print(menu[1]);

            LastState = State;
        }

        if (btns[MIDDLE_BUTTON_IND].isClicked()) //Средняя кнопка
         {
           //set_sound(btn_click_snd);
            State = LastState = _game_mode2;
            _is_game = true;

            randomSeed(random(0, RANDOM_MAX_SEED));

            lcd.clear();
         }

        break;
    case _menu_mode3:
        if (LastState != State)
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd_print(_b_score);
            print_b_score(2);
            lcd.setCursor(0, 1);
            lcd_print(menu[2]);

            LastState = State;
        }

        if (btns[MIDDLE_BUTTON_IND].isClicked()) //Средняя кнопка
         {
           //set_sound(btn_click_snd);
            State = LastState = _game_mode3;
            _is_game = true;

            randomSeed(random(0, RANDOM_MAX_SEED));

            lcd.clear();
         }

        break;
    case _menu_sound:
        if (LastState != State || (is_snd_on != User.sound))
        {
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd_print(menu[3]);
            lcd_print(sound_mode[User.sound]);

            is_snd_on = User.sound;
            LastState = State;
        }
        
        if (btns[MIDDLE_BUTTON_IND].isClicked()) //Средняя кнопка
         {
           //set_sound(btn_click_snd);
            User.sound = !User.sound;
            
            lcd.clear();
         }

        break;
    #else
    case _menu_mode1:
        if (LastState != State)
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd_print(_b_score);
            print_b_score(0);
            lcd.setCursor(0, 1);
            lcd_print(menu[0]);

            LastState = State;
        }

         if (btns[MIDDLE_BUTTON_IND].isClicked() || btns[MIDDLE_BUTTON_IND+1].isClicked()) //Средние кнопки
         {
           //set_sound(btn_click_snd);
            State = LastState = _game_mode1;
            _is_game = true;

            lcd.clear();
         }
         
        break;
    case _menu_mode2:
        if (LastState != State)
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd_print(_b_score);
            print_b_score(1);
            lcd.setCursor(0, 1);
            lcd_print(menu[1]);

            LastState = State;
        }

        if (btns[MIDDLE_BUTTON_IND].isClicked() || btns[MIDDLE_BUTTON_IND+1].isClicked()) //Средние кнопки
         {
           //set_sound(btn_click_snd);
            State = LastState = _game_mode2;
            _is_game = true;

            lcd.clear();
         }

        break;
    case _menu_mode3:
        if (LastState != State)
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd_print(_b_score);
            print_b_score(2);
            lcd.setCursor(0, 1);
            lcd_print(menu[2]);

            LastState = State;
        }

        if (btns[MIDDLE_BUTTON_IND].isClicked() || btns[MIDDLE_BUTTON_IND+1].isClicked()) //Средние кнопки
         {
           //set_sound(btn_click_snd);
            State = LastState = _game_mode3;
            _is_game = true;

            lcd.clear();
         }

        break;
    case _menu_sound:
        if (LastState != State || (is_snd_on != User.sound))
        {
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd_print(menu[3]);
            lcd_print(sound_mode[User.sound]);

            is_snd_on = User.sound;
            LastState = State;
        }

        if (btns[MIDDLE_BUTTON_IND].isClicked() || btns[MIDDLE_BUTTON_IND+1].isClicked()) //Средние кнопки
         {
           set_sound(btn_click_snd);
            User.sound = !User.sound;
            
            lcd.clear();
         }

        break;
    #endif
  }

  if (!_is_game)
  {
    if (btns[0].isClicked()) //Первая кнопка
    {
       set_sound(btn_click_snd);
      State = State - 1;
      if (_menu_mode1 > State) {State = _menu_sound;}
    }
    else if (btns[LED_BTN_COUNT-1].isClicked()) //Последняя кнопка
    {
       set_sound(btn_click_snd);
      State = State + 1;
      if (_menu_sound < State) {State = _menu_mode1;}
    }
  }

  if (isHoldButton() && _is_game) //Если зажаты все кнопки, то заканчиваем игру
  {
     _is_game = false;
  }
}



//####### Функция аппаратного прерывания, сработает при выключении устройства #######
void SetDataInterrupt() //При выключении устройства сохраняет пользовательскую информацию
{
  User._mem_check = 0; //Объявляем, что память была использована
  User._rewrite_cnt++;
  EEPROM.put(data_addr, User); //Записываем текущие данные в теущую область памяти

  set_next_addr(); //Переходим в следующую область памяти
  EEPROM.put(data_addr, User);
}
