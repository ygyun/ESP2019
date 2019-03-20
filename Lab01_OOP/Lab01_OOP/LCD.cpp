// 
// 
// 

#include "LCD.h"

extern int QUEUE_DistanceInCM;
extern int QUEUE_CDSLight;
extern String QUEUE_StringOne;
extern String QUEUE_StringTwo;

void LCDClass::init()
{


}

void LCDClass::init(int rs, int enable, int d4, int d5, int d6, int d7)
{
	m_rs = rs;
	m_enable = enable;
	m_d4 = d4;
	m_d5 = d5;
	m_d6 = d6;
	m_d7 = d7;

	m_strOne = "0123456789012345";
	m_strTwo = "0123456789012345";

	m_lcd = new LiquidCrystal(rs, enable, d4, d5, d6, d7);
	m_lcd->begin(m_cols, m_rows);
	m_lcd->clear();
}

bool LCDClass::process()
{
	m_strOne = QUEUE_StringOne;
	m_strTwo = QUEUE_StringTwo;

	return true;
}

bool LCDClass::operate()
{
	m_lcd->clear();
	m_lcd->print(m_strOne);
	m_lcd->setCursor(0, 1);
	m_lcd->print(m_strTwo);
	delay(m_delayForDisplayInMS);

	return true;
}

LCDClass LCD;

