// 
// 
// 

#include "RGBLED.h"

extern int QUEUE_DistanceInCM;
extern int QUEUE_CDSLight;
extern String QUEUE_StringOne;
extern String QUEUE_StringTwo;

extern int cdsLightVauleForDayNNight;
extern int shortDistance;
extern int middleDistance;
extern int longDistance;
extern int maxAngleOfServoMotor;

RGBLED::RGBLED(int RPin, int GPin, int BPin) :
	m_RPin(RPin), m_GPin(GPin), m_BPin(BPin)
{	
}

void RGBLED::init()
{
	m_RValue = 0;
	m_GValue = 0;
	m_BValue = 0;
}

void RGBLED::start()
{

}

bool RGBLED::wait()
{
	if (QUEUE_CDSLight < cdsLightVauleForDayNNight)
	{
		if (QUEUE_DistanceInCM < shortDistance)
		{
			digitalWrite(m_RPin, 1);
			digitalWrite(m_GPin, 0);
			digitalWrite(m_BPin, 0);
		}
		else if (QUEUE_DistanceInCM < middleDistance)
		{
			digitalWrite(m_RPin, 0);
			digitalWrite(m_GPin, 1);
			digitalWrite(m_BPin, 0);
		}
		else if (QUEUE_DistanceInCM < longDistance)
		{
			digitalWrite(m_RPin, 0);
			digitalWrite(m_GPin, 0);
			digitalWrite(m_BPin, 1);
		}
	}
	else
	{
		digitalWrite(m_RPin, 0);
		digitalWrite(m_GPin, 0);
		digitalWrite(m_BPin, 0);
	}

	return true;
}