//########## Игровые переменные ##########
uint16_t state = 0, cur_lvl = 0; //Последний пройденный уровень и текущий соответственно
byte lvls[MAX_LEVEL]; //Массив для хранения цветов на каждом уровне
size_t cur_user_ans = NONE_LED_BTN, last_user_ans = NONE_LED_BTN; //Переменые для хранения предыдущей и текущей нажатых пользователем кнопок соответственно
bool is_next_lvl = false; //Нужна для корректного перехода на новые уровни

//########## Общие функции ##########
void _set_basic();
void _lose();
void _win();
void _check_time();

Timer delay_led_tmr(_BASIC_LED_BLINK_TIME + LED_BLINK_DELAY_TIME); //Таймер задержки после мигания светодиодов (после мигания игра приостановится на 500 миллисекунд)
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
  
  if (state == 0)
  {
    lcd.clear();
  }

  _check_time();

  if (delay_led_tmr.isStop())
  {
    if (is_next_lvl)
    { 
      blink(lvls[cur_lvl]);
      cur_lvl++;
  
      if (cur_lvl == state){is_next_lvl = false; cur_lvl = 0;}
      else {delay_led_tmr.start();}

      return;
    }
    
    if (cur_lvl == state)
    {
         blink();
         if (state != 0)
         {
           lcd.setCursor(0, 0);
           lcd.print(win[(cur_lvl%2)]);
           lcd_clear_tmr.start();
         }
         
        lvls[state] = random(LED_BTN_COUNT);
        is_next_lvl = true;
        cur_lvl = 0;
        state++;
        
        delay_led_tmr.start();

        return;
    }

      cur_user_ans = getPressedButton(); //Получаем индекс нажатой пользователем кнопку (или NONE_LED_BTN, если твких кнопок нет)

      if (cur_user_ans != NONE_LED_BTN) //Если кнопка была нажата
      {
        if (last_user_ans == NONE_LED_BTN) //Если это первое нажатие
        {
          last_user_ans = cur_user_ans;
          leds[cur_user_ans].setState(HIGH);
        }
      }
      
      if (cur_user_ans != last_user_ans)
      {
          leds[last_user_ans].setState(LOW);

          if (last_user_ans == lvls[cur_lvl])
          {
              cur_lvl++;
              last_user_ans = NONE_LED_BTN;
          }
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

void _lose(){};

void _win(){};

void _check_time()
{
  if (delay_led_tmr.ready())
  {
    delay_led_tmr.stop();
  }
}
