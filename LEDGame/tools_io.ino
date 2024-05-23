<<<<<<< HEAD
=======
#define len(str) sizeof(str)/(sizeof(*str))

#define BLINK_TIME 500 //Период мигания светодиодов
#define TEXT_UPDATE_PRD 550 //Период обновления текса на LCD дисплее

//################### Таймеры ###################
Timer blink_timer(BLINK_TIME); //Таймер для мигания светодиодом
Timer lcd_update_timer(TEXT_UPDATE_PRD);
//###################

//################### Текст ###################

//Текст для меню
const char* menu_text[4][2] = { { "     mode 1     ",
                                  "" },
                                { "     mode 2     ",
                                  "" },
                                { "     mode 3     ",
                                  "" },
                                { "     Sound:     ",
                                  "" } };

const char* scores[2][2] = { { "Score:",
                               "" },
                             { "Best score:",
                               "" } };

//Текст дя игры
const char* start_text[2][2] = { { "      READY     ",
                                   "" },
                                 { "       GO!      ",
                                   "" } }; //Старт игры

const char* lose_text[2][2] = { { "     Sorry,     ",
                                  " but you lost!  " },
                                { " You score:",
                                  "" } };

const char* game_text[2][2] = { { "     Great!     ",
                                  "" },
                                { "   Excellent!   ",
                                  "" } }; //Тект, появляющийся после кадого уровня

const char* win_text[2] = { "Congratulations,",
                            "   you've won!  " };

//###################

void lcd_print(const char** mess, const bool& delay = false) //Функция для отображения текста на дисплей
{
    for (int text_row = 0; text_row < LCD_ROWS; text_row++)
    {
        lcd.setCursor(text_row, 0);
        lcd.print(mess[text_row]);
    }

    if (delay) //Задержка после отображения текста
    {
        lcd_update_timer.start();
        while (!lcd_update_timer.ready()) {};
    }
}

void led_blink(const byte& pin = NONE_LED_BTN)
{
    if (pin == NONE_LED_BTN) //Если пин не указан, то мигание всеми светодиодами
    {
        for (int led : leds) { digitalWrite(led, HIGH); }
        blink_timer.start();
        while (!blink_timer.ready()) {};
        for (int led : leds) { digitalWrite(led, LOW); }

        return;
    }

    //мигание конкретным светодидом
    blink_timer.start();
    while (!blink_timer.ready()) {};
    digitalWrite(pin, HIGH);

    blink_timer.start();
    while (!blink_timer.ready()) {};
    digitalWrite(pin, LOW);
}

void start_game()
{
    //Обновление экрана
    for (int text_i = 0; text_i < len(start_text); text_i++)
    {
        lcd_print(start_text[text_i], true);
    }

    //Мигание светодиодами
    led_blink();

    lcd.clear();
}

void lose()
{
    
}

void win(const bool &last_level = true, const int &level = 1)
{
    /*if (last_level)
    {
        for
    }*/


}

byte get_answer() //Функция для считывания нажатий пользователя на кнопки
{
    for (int btn = 0; btn < LED_BTN_COUNT; btn++)
    {
        if (btns[btn].isPressed()) { return btn; }
    }

    return NONE_LED_BTN;
}

void IOToolsInit()
{
    //Инициализация дисплея
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.clear();

    lcd.print(" A ");

    //Инициализация светодиодов
    for (int i = 0; i < LED_COUNT; i++)
    {
        pinMode(leds[i], OUTPUT);
    }
}
>>>>>>> b5cb184ce936b21dd66100077b3ea53c00840430
