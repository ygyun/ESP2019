// LCD.h

#ifndef _LCD_h
#define _LCD_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <LiquidCrystal.h>
#include "Actuator.h"

class LCD : public Actuator
{
private:
	int m_rs;
	int m_enable;
	int m_d4;
	int m_d5;
	int m_d6;
	int m_d7;
	LiquidCrystal m_lcd;
	int m_rows;
	int m_cols;
	String m_strOne;
	String m_strTwo;

public:
	LCD(int rs, int enable, int d4, int d5, int d6, int d7, int rows, int cols);
	void init();
	void start();
	bool wait();
};

#endif

