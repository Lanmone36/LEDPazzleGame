#define MAX_LEVEL 10001//Максимальное количество уровней

void mode1() //�� ������ ������ � ����������������� ����������� ����� ����
{   
    byte *levels = new byte[MAX_LEVEL];
    byte user_ans;
    int this_level = 0, state = 0;
    bool next_level = true;

    randomSeed(A3);
    start_game();

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

    delete[] levels;
}
