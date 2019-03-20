// LCD.h

#ifndef _LCD_h
#define _LCD_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Actuator.h"
#include <LiquidCrystal.h> 

#define _NUM_ROWS 2;
#define _NUM_COLS 16;
#define _DELAY_FOR_DISPLAY_IN_MS 500

class LCDClass : public ActuatorClass
{
 protected:
	 LiquidCrystal* m_lcd;
	 int m_rs;
	 int m_enable;
	 int m_d4;
	 int m_d5;
	 int m_d6;
	 int m_d7;
	 int m_rows = _NUM_ROWS;
	 int m_cols = _NUM_COLS;
	 String m_strOne;
	 String m_strTwo;
	 long m_delayForDisplayInMS = _DELAY_FOR_DISPLAY_IN_MS;

 public:
	void init();
	void init(int rs, int enable, int d4, int d5, int d6, int d7);
	bool process();
	bool operate();
};

extern LCDClass LCD;


#endif

