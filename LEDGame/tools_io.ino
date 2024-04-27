#define len(str) sizeof(str)/(sizeof(str*))

#define BLINK_TIME 500 //Период мигания светодиодов
#define TEXT_UPDATE_PRD 550 //Период обновления текса на LCD дисплее

//################### Таймеры ###################
Timer blink_timer(BLINK_TIME); //Таймер для мигания светодиодом
Timer lcd_update_timer(TEXT_UPDATE_PRD);
//###################

//################### Текст ###################

//Текст для меню
const char* menu_text[4] = { "     mode 1     ",
                            "     mode 2     ",
                            "     mode 3     ",
                            "     Sound:     " };

const char* best_score = "Best score:";

//Текст дя игры
const char* start_text[2] = { "     READY      ",
                             "       GO!      " }; //Старт игры

const char* lose_text[2][2] = { { "     Sorry,     ",
                                 " but you lost!  "},
                               { " You score:",
                                 "                "} };

const char* game_text[3] = { "Great!",
                            "Excellent!",
                            "Score:" }; //Тект, появляющийся после кадого уровня

const char* win_text[2] = { "Congratulations,",
                           "you've won!" };

//###################

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

void start_game()
{
    //Обновление экрана
    for (int text_i = 0; text_i < len(start_text); text_i++)
    {
        lcd.print(text);

        lcd_update_timer.start();
        while (!lcd_update_timer.ready()) {};

        lcd.setCursor(0, 0);
    }

    //Мигание светодиодами
    for (int led : leds) { digitalWrite(led, HIGH); }
    blink_timer.start();
    while (!blink_timer.ready()) {};
    for (int led : leds) { digitalWrite(led, LOW); }

    lcd.clear();
}

void lose()
{
    lcd.clear();
    lcd.print("A");
}

void win()
{
    //lcd.clear();
    //lcd.print("C");
}

void IOToolsInit()
{
    //Инициализация дисплея
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);

    //Инициализация светодиодов
    for (int i = 0; i < LED_COUNT; i++)
    {
        pinMode(leds[i], OUTPUT);
    }
}
