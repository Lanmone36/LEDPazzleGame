#pragma once

struct Note
{
	Note(const uint16_t& note, const uint16_t& tmr)
	{
		_tmr = tmr;
		_note = note;
	}

	uint16_t _tmr;
	uint16_t _note;
};

bool operator==(const Note& f, const Note& s)
{
	return (f._note == s._note) && (f._tmr == s._tmr);
}

Note SND_END = { 0, 0 };

class Piezzo 
{
public:
	Piezzo(const byte& _pin, const bool& repeat = false);
	~Piezzo();

	void set_sound(Note* sound);
	void play(bool restart = false);
	void pause();
	void reset();
	void update();

	bool isPlaying();

	Note* get_sound();
private:
	byte _pin;
	Timer* _tmr = nullptr;
	Note* _snd = nullptr;

	bool _isPlay;
	bool _repeat;
	byte _note_cnt;
};