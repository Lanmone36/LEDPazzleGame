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
