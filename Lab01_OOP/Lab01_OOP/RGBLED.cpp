// 
// 
// 

#include "RGBLED.h"

extern int QUEUE_DistanceInCM;
extern int QUEUE_CDSLight;
extern String QUEUE_StringOne;
extern String QUEUE_StringTwo;

void RGBLEDClass::init()
{


}

void RGBLEDClass::init(int RPin, int GPin, int BPin)
{
	m_RPin = RPin;
	m_GPin = GPin;
	m_BPin = BPin;
	
	m_RValue = 0;
	m_GValue = 0;
	m_BValue = 0;
}

bool RGBLEDClass::process()
{
	if (QUEUE_CDSLight < 800)
	{
		if (QUEUE_DistanceInCM < 5)
		{
//			m_RValue = 255;
			m_RValue = 1;
			m_GValue = 0;
			m_BValue = 0;
		}
		else if (QUEUE_DistanceInCM < 10)
		{
			m_RValue = 0;
//			m_GValue = 255;
			m_GValue = 1;
			m_BValue = 0;
		}
		else if (QUEUE_DistanceInCM < 15)
		{
			m_RValue = 0;
			m_GValue = 0;
//			m_BValue = 255;
			m_BValue = 1;
		}
	}
	else
	{
		m_RValue = 0;
		m_GValue = 0;
		m_BValue = 0;
	}

	return true;
}

bool RGBLEDClass::operate()
{
//	analogWrite(m_RPin, m_RValue);
//	analogWrite(m_GPin, m_GValue);
//	analogWrite(m_BPin, m_BValue);

	digitalWrite(m_RPin, m_RValue);
	digitalWrite(m_GPin, m_GValue);
	digitalWrite(m_BPin, m_BValue);
	delay(m_delayForRGBLEDInMS);
}

RGBLEDClass RGBLED;

