//########## Игровые переменные ##########
uint8_t state = 0, cur_lvl = 0; //Последний пройденный уровень и текущий соответственно
byte lvls[MAX_LEVEL]; //Массив для хранения цветов на каждом уровне
size_t cur_user_ans = NONE_LED_BTN, last_user_ans = NONE_LED_BTN; //Переменые для хранения предыдущей и текущей нажатых пользователем кнопок соответственно
bool is_next_lvl = false; //Нужна для корректного перехода на новые уровни

//########## Общие функции ##########
void _set_basic();
void _lose();
void _win();
void check_time();

Timer delay_tmr(_BASIC_LED_BLINK_TIME + 500); //Таймер задержки после мигания светодиодов (после мигания игра приостановится на 500 миллисекунд)
/*Вместо таймеров и прочего можно было просто использовать delay.
В этом проекте это даже более удобно и уместно.
Но мне хотелоь сделать полностью "синхронный" код*/

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
      leds.blink(lvls[cur_lvl]);
      cur_lvl++;
  
      if (cur_lvl == state){is_next_lvl = false; cur_lvl = 0;}

      delay_tmr.start();

      return;
    }
    
    if (cur_lvl == state)
    {
        leds.blink();
    
        lvls[state] = random(LED_BTN_COUNT);
        is_next_lvl = true;
        cur_lvl = 0;
        state++;
        delay_tmr.start();

        return;
    }

      cur_user_ans = btns.getPressedButton(); //Получаем нажатую пользователем кнопку (или NONE_LED_BTN, если твких кнопок нет)

      if (cur_user_ans != NONE_LED_BTN) //Если кнопка была нажата
      {
        if (last_user_ans == NONE_LED_BTN) //Если это первое нажатие
        {
          last_user_ans = cur_user_ans;
          leds.setState(cur_user_ans, HIGH);
        }
      }
      
      if (cur_user_ans != last_user_ans)
      {
          leds.setState(last_user_ans, LOW);

          if (last_user_ans == lvls[cur_lvl]) {cur_lvl++; last_user_ans = NONE_LED_BTN;}
          else {_set_basic(); _lose();}
      }
    }
}

void game_mode2(){};

void game_mode3(){};

void _set_basic()
{
  state = 0;
  is_next_lvl = false;
  last_user_ans = NONE_LED_BTN;
  cur_lvl = 0;
}

void _lose(){lcd_func.print(test111);};

void _win(){};

void check_time()
{
  if (delay_tmr.ready())
  {
    delay_tmr.stop();
  }
}
