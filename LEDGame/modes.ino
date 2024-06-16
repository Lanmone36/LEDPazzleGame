//########## Игровые переменные ##########
uint8_t state = 0, cur_lvl = 0; //Последний пройденный уровень и текущий соответственно
byte lvls[MAX_LEVEL]; //Массив для хранения цветов на каждом уровне
bool is_next_lvl = false; //Нужна для корректного перехода на новые уровни

//########## Общие функции ##########
void _set_basic();
void _lose();
void _win();
void check_time();

Timer delay_tmr(1000); //Таймер задержки после мигания светодиодов

void game_mode1()
{
  if (state == MAX_LEVEL)
  {
    _win();
    
    _set_basic();
    return;
  }

  check_time();

  if (delay_tmr.isStop())
  {
    if (is_next_lvl)
    { 
      if (!leds.getState(lvls[cur_lvl-1])) //Если предыдущий светодиод "догороел"
      {
        leds.blink(lvls[cur_lvl]);
        cur_lvl++;

        delay_tmr.start();
      }
  
      if (cur_lvl == state){is_next_lvl = false; cur_lvl = 0;}
    }
    else
    {
      leds.blink();

      delay_tmr.start();
    
      lvls[state] = random(LED_BTN_COUNT);
      is_next_lvl = true;
      state++;
    }
  }
}

void game_mode2(){};

void game_mode3(){};

void _set_basic()
{
  state = 0;
  is_next_lvl = false;
}

void lose(){};

void win(){};

void check_time()
{
  if (delay_tmr.ready())
  {
    delay_tmr.stop();
  }
}
