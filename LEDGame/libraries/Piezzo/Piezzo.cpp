#include "Piezzo.h"

Piezzo::Piezzo(const byte& _pin, const bool& repeat = false)
{
	this->_pin = _pin;
	this->_tmr = new Timer();

	this->_isPlay = false;
	this->_repeat = repeat;
	this->_note_cnt = 255;
}

Piezzo::~Piezzo() 
{
	delete this->_tmr;
	delete this->_snd;
}

void Piezzo::set_sound(Note* sound) 
{
	this->reset();

	//delete this->_snd;
	this->_snd = sound;
}

void Piezzo::play(bool restart = false)
{
	this->_isPlay = true;
	
	if (restart) { this->_note_cnt = 255; }
}

void Piezzo::reset() 
{
	this->_tmr->stop();
	this->_isPlay = false;
	this->_note_cnt = 255;

	noTone(this->_pin);
}

void Piezzo::pause()
{
	this->_isPlay = false;
	noTone(this->_pin);
}

void Piezzo::update()
{
	if (this->_isPlay && this->_snd != nullptr) 
	{
		/*Serial.print("if 1 ");
		Serial.print(this->_tmr->ready());
		Serial.print(" ");
		Serial.println(this->_note_cnt);*/
		if (this->_tmr->ready() || this->_note_cnt == 255)
		{
			/*Serial.println("if 2");*/
			this->_note_cnt++;

			if (this->_snd[this->_note_cnt] == SND_END)
			{
				this->reset();

				if (this->_repeat) { this->_isPlay = true; }

				return;
			}

			this->_tmr->setPeriod(this->_snd[this->_note_cnt]._tmr * 1.3);
			this->_tmr->start();
			tone(this->_pin, this->_snd[this->_note_cnt]._note);
		}
	}
}

bool Piezzo::isPlaying() 
{
	return this->_isPlay;
}

Note* Piezzo::get_sound()
{
	return this->_snd;
}
