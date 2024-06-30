#pragma once

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class LCDManager
{
public:
	LCDManager(const LiquidCrystal_I2C* lcd,
		       const uint8_t& rows);
	~LCDManager();

	void print(const char* mess,
		       const uint8_t& row,
		       const bool& full_clear = false);
	void begin();

private:
	LiquidCrystal_I2C* _lcd = nullptr;
	char** _buff = nullptr;
	uint8_t _rows;
};