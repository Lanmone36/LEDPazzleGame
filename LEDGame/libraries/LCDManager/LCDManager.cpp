#include "LCDManager.h"

LCDManager::LCDManager(const LiquidCrystal_I2C* lcd, const uint8_t& rows)
{
	this->_lcd = lcd;
	this->_buff = new char*[rows];
	this->_rows = rows;
}

LCDManager::~LCDManager()
{
	delete this->_lcd;

	for (uint8_t row = 0; row < this->_rows; row++)
	{
		delete[] this->_buff[row];
	}
	delete[] this->_buff;
}

void LCDManager::print(const char* mess, const uint8_t& row, const bool& full_clear = false)
{
	if (this->_buff[row] != mess)
	{
		this->_buff[row] = mess;

		if (full_clear) {this->_lcd->clear();}
		this->_lcd->setCursor(0, row);
		this->_lcd->print(mess);
	}
}

void LCDManager::begin()
{
	this->_lcd->init();
	this->_lcd->backlight();
}