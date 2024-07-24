#include <Arduino.h>

//########## Весь текст ##########
// Результаты
const char _score[] PROGMEM   =   "     score: ";
const char _b_score[] PROGMEM = "best score: ";
// Проигрышь
const char _lose[] PROGMEM    =     "  You've lost!  ";
// Победа
const char _win_1[] PROGMEM   =   "  Excellently!  ";
const char _win_2[] PROGMEM   =   "     Great!     ";
const char _win_3[] PROGMEM   =   "Congratulations!";
const char _win_4[] PROGMEM   =   "  You've won!!  ";
// Старт игры
const char _start_1[] PROGMEM = "     READY!     ";
const char _start_2[] PROGMEM = "      !GO!      ";
// Меню
const char _menu_1[] PROGMEM  =  "     mode 1     ";
const char _menu_2[] PROGMEM  =  " mode 2(in dev.)";
const char _menu_3[] PROGMEM  =  " mode 3(in dev.)";
const char _menu_4[] PROGMEM  =  "   Sounds: ";
//Звук
const char _sound_1[] PROGMEM =  "OFF";
const char _sound_2[] PROGMEM =  "ON";
//##########

const char* const menu[] = {_menu_1,
                            _menu_2,
                            _menu_3,
                            _menu_4};

const char* const final_win[] = {_win_3,
                                 _win_4};

const char* const start[] = { _start_1,
                             _start_2 };

const char* const lose[] = {_lose,
                            _score};

const char* const win[] = {_win_1,
                           _win_2};

const char* const sound_mode[] = {_sound_1,
                                  _sound_2};
