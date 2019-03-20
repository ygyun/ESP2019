// 
// 
// 

#include "Proximity.h"

extern int QUEUE_DistanceInCM;
extern int QUEUE_CDSLight;
extern String QUEUE_StringOne;
extern String QUEUE_StringTwo;

extern int cdsLightVauleForDayNNight;
extern int shortDistance;
extern int middleDistance;
extern int longDistance;
extern int maxAngleOfServoMotor;

Proximity::Proximity(int inPin, int outPin, int retensionTimeForFiringWaveInMS) :
	m_inPin(inPin),
	m_outPin(outPin),
	m_retensionTimeForFiringWaveInMS(retensionTimeForFiringWaveInMS)
{	
}

void Proximity::init()
{
	m_reflectionTimeInMS = 0;
}

void Proximity::start()
{

}

bool Proximity::wait()
{
	digitalWrite(m_outPin, HIGH);
	delayMicroseconds(m_retensionTimeForFiringWaveInMS);
	digitalWrite(m_outPin, LOW);

	m_reflectionTimeInMS = pulseIn(m_inPin, HIGH);
	if (m_reflectionTimeInMS == 0)
	{
		return false;
	}

	QUEUE_DistanceInCM = m_reflectionTimeInMS / 58.2;
	QUEUE_StringTwo = "Distance: ";
	QUEUE_StringTwo += QUEUE_DistanceInCM;
	QUEUE_StringTwo += "cm";

	return true;
}
