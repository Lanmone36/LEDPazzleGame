//########## Игровые переменные ##########
uint8_t state = 0, cur_lvl = 0; //Последний пройденный уровень и текущий соответственно
byte lvls[MAX_LEVEL]; //Массив для хранения цветов на каждом уровне
byte cur_user_ans = NONE_LED_BTN, last_user_ans; //Переменые для хранения предыдущей и текущей нажатых пользователем кнопок соответственно
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
      Serial.println(1);
      leds.blink(lvls[cur_lvl]);
      cur_lvl++;
  
      if (cur_lvl == state){is_next_lvl = false; cur_lvl = 0;}

      delay_tmr.start();

      return;
    }
    
    if (cur_lvl == 0)
    {
      Serial.println(0);
        leds.blink();
    
        lvls[state] = random(LED_BTN_COUNT);
        is_next_lvl = true;
        state++;
        delay_tmr.start();
          
        return;
    }

//      cur_user_ans = btns.getPressedButton();
//
//      if (cur_user_ans != NONE_LED_BTN)
//      {
//        if (last_user_ans == NONE_LED_BTN)
//        {
//          last_user_ans = cur_user_ans;
//          leds.setState(cur_user_ans, HIGH);
//          }
//        else if (cur_user_ans != last_user_ans && last_user_ans != NONE_LED_BTN)
//      {
//          leds.setState(last_user_ans, LOW);
//
//          if (last_user_ans == lvls[cur_lvl]) {cur_lvl++;}
//          else {_set_basic();}
//          delay_tmr.start();
//      }
//      }
//      else
//      {last_user_ans = NONE_LED_BTN;
//        }
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

void lose(){};

void win(){};

void check_time()
{
  if (delay_tmr.ready())
  {
    delay_tmr.stop();
  }
}
