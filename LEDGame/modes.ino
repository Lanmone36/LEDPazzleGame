//########## Игровые переменные ##########
uint8_t state = 0, cur_lvl = 0; //Последний пройденный уровень и текущий соответственно
byte lvls[MAX_LEVEL]; //Массив для хранения цветов на каждом уровне
bool is_next_level = true: 1 //Нужна для корректного перехода на новые уровних

void game_mode1()
{
  if (is_next_level)
  {
    is_next_level = false;
    lvls[state] = random(LED_BTN_COUNT);

    for (uint8_t lvl_ind = 0; lvl_ind <= state; lvl_ind++){leds.blink(lvls[lvl_ind]);}
  }
}



void game_mode2{}{};



void game_mode3(){};
