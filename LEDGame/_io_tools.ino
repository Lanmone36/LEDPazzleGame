void leds_btns_update() {
  for (byte _ind = 0; _ind < LED_BTN_COUNT; _ind++)
  {
    leds[_ind].update();
    btns[_ind].update();
  }
}

void lcd_pz_update()
{
  pz.update();
  if (lcd_clear_tmr.ready())
  {
    lcd.clear();
    lcd_clear_tmr.stop();

    lcd_clear_tmr.setPeriod(LCD_CLEAR_TIME); //Если вдруг период был изменён
  }
}

byte randomSet(byte count = 1)
{
  byte _ans = 0;
  byte _place;

  while (count > 0)
  {
    _place = random(LED_BTN_COUNT);
    if (!bitRead(_ans, _place))
    {
      bitSet(_ans, _place);
      count--;
    }
  }

  return _ans;
}

void blink(const byte& led_ind = NONE_LED_BTN)
{
  if (led_ind == NONE_LED_BTN) //Если индекс светодиода не указан, то мигает всеми
  {
    for (byte _led_ind = 0; _led_ind < LED_BTN_COUNT; _led_ind++)
    {
      leds[_led_ind].blink();
    }

    return;
  }

  for (byte _led_ind = 0; _led_ind < LED_BTN_COUNT; _led_ind++)
   {
      if (bitRead(led_ind, _led_ind))
      {
          leds[_led_ind].blink();
      }
   }
}

void setState(const byte& led_ind = NONE_LED_BTN, bool state = HIGH)
{
  if (led_ind == NONE_LED_BTN) //Если индекс светодиода не указан, то мигает всеми
  {
    for (byte _led_ind = 0; _led_ind < LED_BTN_COUNT; _led_ind++)
    {
      leds[_led_ind].setState(state);
    }

    return;
  }

  for (byte _led_ind = 0; _led_ind < LED_BTN_COUNT; _led_ind++)
   {
    leds[_led_ind].setState(bitRead(led_ind, _led_ind)&state);
   }
}

bool isHoldButton(const byte& btn_ind = NONE_LED_BTN)
{
  if (btn_ind == NONE_LED_BTN) //Если индекс кнопки не указан, то проверяем, зажаты ли все кнопки
  {
    for (byte _btn_ind = 0; _btn_ind < LED_BTN_COUNT; _btn_ind++)
    {
      if (!btns[_btn_ind].isHolded()) {return false;}
    }

    return true;
  }

  return btns[btn_ind].isHolded();
}

byte getPressedButton(bool only_one = true)
{
  byte _ans;
  for (byte _btn_ind = 0; _btn_ind < LED_BTN_COUNT; _btn_ind++)
  {
    bitWrite(_ans, _btn_ind, btns[_btn_ind].isPressed());
    if (bitRead(_ans, _btn_ind) && only_one)
    {
      break;
    }
  }

  if (_ans == 0)
  {
      return NONE_LED_BTN;
  }
  
  return _ans;
}

void set_sound(Note* snd)
{
  if (User.sound)
  {
    pz.set_sound(snd);
    pz.play();
  }

    //tone(PZ, NOTE_A2, 100);
}

void print_b_score(const byte& game_mode_ind)
{
  lcd.print(User.b_scores[game_mode_ind]);
}
