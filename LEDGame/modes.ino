//########## Игровые переменные ##########
uint16_t state = 0, cur_lvl = 0; //Последний пройденный уровень и текущий соответственно
byte lvls[MAX_LEVEL]; //Массив для хранения цветов на каждом уровне
size_t cur_user_ans = NONE_LED_BTN, last_user_ans = NONE_LED_BTN; //Переменые для хранения предыдущей и текущей нажатых пользователем кнопок соответственно
bool is_next_lvl = false; //Нужна для корректного перехода на новые уровни
bool is_lose = false, is_start = true;
byte l_s_cnt = 0;
//##########

//########## Общие функции ##########
void _set_basic();
void _lose_();
void _win_();
void _start_();
void _check_time();
void _set_b_score();
//##########

Timer delay_led_tmr(_BASIC_LED_BLINK_TIME + LED_BLINK_DELAY_TIME); //Таймер задержки после мигания светодиодов (после мигания игра приостановится на 500 миллисекунд)
Timer delay_lcd_tmr(LCD_DELAY_TIME); //Таймер для задержки времени после вывода текста на дисплей
Timer back_delay_tmr(BACK_DELAY_TIME); //Таймер для задержки перед возвращением в меню
/*Вместо таймеров и прочего можно было просто использовать delay.
В этом проекте это даже более удобно и уместно.
Но мне хотелоь сделать полностью "синхронный" код*/

void game_mode1()
{
  //####### Обработка выхода в меню #######
  if (back_delay_tmr.ready() || (!_is_game)) //Если таймер выхода в меню закончился или игра была остановлена
  {
    _set_b_score();
    
    State = _menu_mode1; //Выходим в меню
    _is_game = false;

    setState(last_user_ans, LOW); //Если игра была остановлена, то выключаем последний светодиод
    
    _set_basic();

    back_delay_tmr.stop();

    return;
  }
  
  if (!back_delay_tmr.isStop()) {return;} //Если таймер выхода начался, не запускаем игру
  //##############
    
  _check_time();
  
  if (state == MAX_LEVEL) //Если пройдены все уровни
  {
    _win_();
    
    _set_basic();
    return;
  }

  if (is_lose) //Поражение
  {
    _lose_();
    
    return;
  }

  if (is_start) //Если счётчик начала игры не закончился (идёт "вступление")
  {
    _start_();

    return;
  }

  //####### Основной код игры #######
  if (delay_led_tmr.isStop())
  {
    if (is_next_lvl)
    { 
      blink(lvls[cur_lvl]);
      set_sound(blink_sound);
      cur_lvl++;
  
      if (cur_lvl == state){is_next_lvl = false; cur_lvl = 0;}
      else {delay_led_tmr.start();}

      return;
    }
    
    if (cur_lvl == state) //Если уровень пройден
    {
         blink();
         if (state != 0)
         {
           lcd.setCursor(0, 0);
           lcd_print(win[(bool)(cur_lvl%5)]);
           lcd_clear_tmr.start();

           if (cur_lvl%5)
           {
              set_sound(next_lvl_sound_special);
           }
           else
           {
              set_sound(next_lvl_sound_basic);
           }
         }
         
        lvls[state] = randomSet(1);
        is_next_lvl = true;
        cur_lvl = 0;
        state++;
        
        delay_led_tmr.start();

        return;
    }

      cur_user_ans = getPressedButton(); //Получаем индекс нажатой пользователем кнопки (или NONE_LED_BTN, если таких кнопок нет)

      if (cur_user_ans != NONE_LED_BTN) //Если кнопка была нажата
      {
        if (last_user_ans == NONE_LED_BTN) //Если это первое нажатие
        {
          last_user_ans = cur_user_ans;
          setState(cur_user_ans, HIGH);
        }
      }
      
      if (cur_user_ans != last_user_ans)
      {
          setState(last_user_ans, LOW);

          if (last_user_ans == lvls[cur_lvl])
          {
              cur_lvl++;
              last_user_ans = NONE_LED_BTN;
          }
          else {is_lose = true;}
      }
    }
    //##############
}

void game_mode2()
{
  //####### Обработка выхода в меню #######
  if (back_delay_tmr.ready() || (!_is_game)) //Если таймер выхода в меню закончился или игра была остановлена
  {
    _set_b_score();
    
    State = _menu_mode2; //Выходим в меню
    _is_game = false;

     setState(last_user_ans, LOW); //Если игра была остановлена, то выключаем последний светодиод
    
    _set_basic();

    back_delay_tmr.stop();

    return;
  }
  
  if (!back_delay_tmr.isStop()) {return;} //Если таймер выхода начался, не запускаем игру
  //##############
    
  _check_time();
  
  if (state == MAX_LEVEL) //Если пройдены все уровни
  {
    _win_();
    
    _set_basic();
    return;
  }

  if (is_lose) //Поражение
  {
    _lose_();
    
    return;
  }

  if (is_start) //Если счётчик начала игры не закончился (идёт "вступление")
  {
    _start_();

    return;
  }

  //####### Основной код игры #######
  if (delay_led_tmr.isStop())
  {
    if (is_next_lvl)
    { 
      lvls[cur_lvl] = randomSet(1);
      blink(lvls[cur_lvl]);
      set_sound(blink_sound);
      cur_lvl++;
  
      if (cur_lvl == state){is_next_lvl = false; cur_lvl = 0;}
      else {delay_led_tmr.start();}

      return;
    }
    
    if (cur_lvl == state) //Если уровень пройден
    {
         blink();
         if (state != 0)
         {
           lcd.setCursor(0, 0);
           lcd_print(win[(bool)(cur_lvl%5)]);
           lcd_clear_tmr.start();

           if (cur_lvl%5)
           {
              set_sound(next_lvl_sound_special);
           }
           else
           {
              set_sound(next_lvl_sound_basic);
           }
         }
         
        is_next_lvl = true;
        cur_lvl = 0;
        state++;
        
        delay_led_tmr.start();

        return;
    }

      cur_user_ans = getPressedButton(); //Получаем индекс нажатой пользователем кнопки (или NONE_LED_BTN, если таких кнопок нет)

      if (cur_user_ans != NONE_LED_BTN) //Если кнопка была нажата
      {
        if (last_user_ans == NONE_LED_BTN) //Если это первое нажатие
        {
          last_user_ans = cur_user_ans;
          setState(cur_user_ans, HIGH);
        }
      }
      
      if (cur_user_ans != last_user_ans)
      {
          setState(last_user_ans, LOW);

          if (last_user_ans == lvls[cur_lvl])
          {
              cur_lvl++;
              last_user_ans = NONE_LED_BTN;
          }
          else {is_lose = true;}
      }
    }
    //##############
}


void game_mode3()
{
  //####### Обработка выхода в меню #######
  if (back_delay_tmr.ready() || (!_is_game)) //Если таймер выхода в меню закончился или игра была остановлена
  {
    _set_b_score();
    
    State = _menu_mode3; //Выходим в меню
    _is_game = false;

     setState(last_user_ans, LOW); //Если игра была остановлена, то выключаем последние светодиоды
    
    _set_basic();

    back_delay_tmr.stop();

    return;
  }
  
  if (!back_delay_tmr.isStop()) {return;} //Если таймер выхода начался, не запускаем игру
  //##############
    
  _check_time();
  
  if (state == MAX_LEVEL) //Если пройдены все уровни
  {
    _win_();
    
    _set_basic();
    return;
  }

  if (is_lose) //Поражение
  {
    _lose_();
    
    return;
  }

  if (is_start) //Если счётчик начала игры не закончился (идёт "вступление")
  {
    _start_();

    return;
  }

  //####### Основной код игры #######
  if (delay_led_tmr.isStop())
  {
    if (is_next_lvl)
    { 
      lvls[cur_lvl] = randomSet(random(1, LED_BTN_COUNT));
      blink(lvls[cur_lvl]);
      set_sound(blink_sound);
      cur_lvl++;
  
      if (cur_lvl == state){is_next_lvl = false; cur_lvl = 0;}
      else {delay_led_tmr.start();}

      return;
    }
    
    if (cur_lvl == state) //Если уровень пройден
    {
         blink();
         if (state != 0)
         {
           lcd.setCursor(0, 0);
           lcd_print(win[(bool)(cur_lvl%5)]);
           lcd_clear_tmr.start();

           if (cur_lvl%5)
           {
              set_sound(next_lvl_sound_special);
           }
           else
           {
              set_sound(next_lvl_sound_basic);
           }
         }
         
        is_next_lvl = true;
        cur_lvl = 0;
        state++;
        
        delay_led_tmr.start();

        return;
    }

      cur_user_ans = getPressedButton(false); //Получаем индекс нажатой пользователем кнопки (или NONE_LED_BTN, если таких кнопок нет)

      if (cur_user_ans != NONE_LED_BTN) //Если кнопка была нажата
      {
        if (last_user_ans < cur_user_ans || last_user_ans == NONE_LED_BTN) //Если это первое нажатие
        {
          last_user_ans = cur_user_ans;
          setState(cur_user_ans, HIGH);
        }
      }
      
      if (cur_user_ans == NONE_LED_BTN && last_user_ans != NONE_LED_BTN)
      {
          setState(last_user_ans, LOW);

          if (last_user_ans == lvls[cur_lvl])
          {
              cur_lvl++;
              last_user_ans = NONE_LED_BTN;
          }
          else {is_lose = true;}
      }
    }
    //##############
}


void _set_basic()
{
  state = 0;
  is_next_lvl = false;
  last_user_ans = NONE_LED_BTN;
  cur_lvl = 0;
  is_lose = false;
  is_start = true;
  l_s_cnt = 0;

  delay_lcd_tmr.stop();
  delay_led_tmr.stop();
  back_delay_tmr.stop();
}

void _lose_()
{
   if (delay_lcd_tmr.isStop()) {delay_lcd_tmr.start(); lcd.setCursor(0, 0); lcd_print(lose[l_s_cnt]); set_sound(lose_sound);}

   if (delay_lcd_tmr.ready())
   {
      l_s_cnt++;
      
      lcd.clear(); //Нужна для удаления символов лишней строки, так как длина строки _score меньше
                   //длины строки дисплея (сделано для тог, чтобы было удобно выводить очки)
      lcd_print(lose[l_s_cnt]);
   }

   if (l_s_cnt == 1)
   {
    delay_lcd_tmr.stop();
    lcd.print(state-1);

    back_delay_tmr.start();
   }
}

void _start_()
{
   if (delay_lcd_tmr.isStop()) {delay_lcd_tmr.start(); lcd.setCursor(0, 0); lcd_print(start[l_s_cnt]); set_sound(start_sound);}

   if (delay_lcd_tmr.ready())
   {
      l_s_cnt++;
      
      lcd.clear();
      lcd_print(start[l_s_cnt]);
   }

   if (l_s_cnt == 1)
   {
    delay_lcd_tmr.stop();
    is_start = false;
    l_s_cnt = 0;

    lcd_clear_tmr.setPeriod(LCD_DELAY_TIME);
    lcd_clear_tmr.start();
   }
}

void _win_(){set_sound(win_sound);};

void _check_time()
{
  if (delay_led_tmr.ready())
  {
    delay_led_tmr.stop();
  }
}

void _set_b_score()
{
  if (User.b_scores[State] < (state-1))
  {
    User.b_scores[State] = (state-1);
    SetDataInterrupt();
  }
}
