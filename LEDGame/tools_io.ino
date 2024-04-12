#define BLINK_TIME 500 //Период мигания светодиодов
#define TEXT_UPDATE_PRD 550 //Период обновления текса на LCD дисплее

//################### Таймеры ###################
Timer blink_timer(BLINK_TIME); //Таймер для мигания светодиодом
Timer lcd_update_timer(TEXT_UPDATE_PRD);

//################### Текст ###################

//Текст для меню
const char* menu_text[] = { "     mode 1     ",
                            "     mode 2     ",
                            "     mode 3     ",
                            "     Sound:     " };

const char* best_score = "Best score:";

//Текст дя игры
const char* start_text[] = { "     READY      ",
                             "       GO!      " }; //Старт игры

const char* lose_text[2][2] = { { "     Sorry,     ",
                                 " but you lost!  "},
                               { " You score:",
                                 "                "} };

const char* game_text[] = { "Great!",
                            "Excellent!",
                            "Score:" }; //Тект, появляющийся после кадого уровня

const char* win_text[] = { "Congratulations,",
                           "you've won!" };

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
    lcd.print(start_text[0]);

    lcd_update_timer.start();
    while (!lcd_update_timer.ready()) {};

    lcd.home();
    lcd.print(start_text[1]);

    for (int led : leds) { digitalWrite(led, HIGH); }
    blink_timer.start();
    while (!blink_timer.ready()) {};
    for (int led : leds) { digitalWrite(led, LOW); }

    lcd.clear();
}

void lose()
{
    
}

void win()
{
    
}