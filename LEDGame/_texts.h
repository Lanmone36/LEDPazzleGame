#include <Arduino.h>

//########## Весь текст ##########
// Результаты
const char _score[] = "     score: ";
const char _b_score[] = "best score: ";
// Проигрышь
const char lose[] = "  You've lost!  ";
// Победа
const char _win_1[] =  "     Great!     ";
const char _win_2[] = "  Excellently!  ";
const char _win_3[] = "Congratulations!";
const char _win_4[] = "  You've won!!  ";
// Старт игры
const char _start_1[] = "READY!";
const char _start_2[] = "GO!";
// Меню
const char _menu_1[] = "     mode 1     ";
const char _menu_2[] = "     mode 2     ";
const char _menu_3[] = "     mode 3     ";
const char _menu_4[] = "   Sounds: ";
//##########

const char* const menu[] = {_menu_1,
                            _menu_2,
                            _menu_3,
                            _menu_4};

const char* const final_win[] = {_win_3,
                                 _win_4};

const char* const win[] = {_win_1,
                           _win_2};

const char* const start[] = {_start_1,
                             _start_2};