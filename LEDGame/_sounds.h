#include "pitches.h"

//Шаблон: Note [some_snd] = {{Нота, время проигрывания}, {Нота, время проигрывания}, ... , SND_END}

const Note win_sound[1]  = { SND_END };
const Note lose_sound[6] = { {NOTE_5, 150}, {NOTE_6, 150}, {NOTE_3, 150}, {NOTE_6, 250}, {NOTE_3, 550}, SND_END };
const Note start_sound[6]  = { {NOTE_10, 250}, {PAUSE_NOTE, 63}, {NOTE_10, 290}, {PAUSE_NOTE, 63},  {NOTE_15, 333}, SND_END };
const Note next_lvl_sound_basic[2]  = { {NOTE_10, 300}, SND_END };
const Note next_lvl_sound_special[2] = { {NOTE_15, 300}, SND_END };

const Note btn_click_snd[2]  = {{NOTE_10, 50}, SND_END};
const Note blink_sound[2] = {{NOTE_5, 500}, SND_END};
