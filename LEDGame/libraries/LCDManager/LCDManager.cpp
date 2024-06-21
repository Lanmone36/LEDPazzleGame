#include "LCDManager.h"

LCDManager::LCDManager(const LiquidCrystal_I2C* lcd, const uint8_t& rows)
{
	this->_lcd = lcd;
	this->_rows = rows;
}

LCDManager::~LCDManager()
{
	delete this->_lcd;
}

void LCDManager::print(const char** mess, const bool& full_clear = false)
{
	if (full_clear) { this->_lcd->clear(); }

	for (byte row = 0; row < this->_rows; row++)
	{
		this->_lcd->setCursor(0, row);
		this->_lcd->print(mess[row]);
	}
}

void LCDManager::begin()
{
	this->_lcd->init();
	this->_lcd->backlight();
}