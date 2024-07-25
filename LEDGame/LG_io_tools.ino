void leds_btns_update() {
  for (byte _ind = 0; _ind < LED_BTN_COUNT; _ind++)
  {
    leds[_ind].update();
    btns[_ind].update();
  }
}

void lcd_update()
{
  if (lcd_clear_tmr.ready())
  {
    lcd.clear();
    lcd_clear_tmr.stop();

    lcd_clear_tmr.setPeriod(LCD_CLEAR_TIME); //Если вдруг период был изменён
  }
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

  leds[led_ind].blink();
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

byte getPressedButton()
{
  for (byte _btn_ind = 0; _btn_ind < LED_BTN_COUNT; _btn_ind++)
  {
    if (btns[_btn_ind].isPressed())
    {
      return _btn_ind; //Возвращает индекс нажатой кнопки
    }
  }

  return NONE_LED_BTN;
}
