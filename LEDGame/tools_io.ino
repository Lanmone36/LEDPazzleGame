#define BLINK_TIME 500 //Период мигания светодиодов

Timer blink_timer(BLINK_TIME); //Таймер для мигания светодиодом

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
    for (int led : leds){ digitalWrite(led, HIGH); }
    blink_timer.start();
    while (!blink_timer.ready()) {};
    for (int led : leds) { digitalWrite(led, LOW); }
}

void lose()
{
    Serial.println("Sorry, but yoe lost!");
}

void win()
{
    Serial.println("Congratulations, you've won!");
}
