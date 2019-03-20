// 
// 
// 

#include "LCD.h"

extern int QUEUE_DistanceInCM;
extern int QUEUE_CDSLight;
extern String QUEUE_StringOne;
extern String QUEUE_StringTwo;

extern int cdsLightVauleForDayNNight;
extern int shortDistance;
extern int middleDistance;
extern int longDistance;
extern int maxAngleOfServoMotor;

LCD::LCD(int rs, int enable, int d4, int d5, int d6, int d7, int rows, int cols) :
	m_rs(rs),
	m_enable(enable),
	m_d4(d4),
	m_d5(d5),
	m_d6(d6),
	m_d7(d7),
	m_rows(rows),
	m_cols(cols),
	m_lcd(LiquidCrystal(rs, enable, d4, d5, d6, d7))
{	
}

void LCD::init()
{
	m_lcd.begin(m_cols, m_rows);
	m_lcd.clear();
}

void LCD::start()
{

}

bool LCD::wait()
{
	m_lcd.clear();
	m_lcd.print(QUEUE_StringOne);
	m_lcd.setCursor(0, 1);
	m_lcd.print(QUEUE_StringTwo);

	return true;
}
