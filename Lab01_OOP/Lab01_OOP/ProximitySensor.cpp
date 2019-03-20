// 
// 
// 

#include "ProximitySensor.h"
extern int QUEUE_DistanceInCM;
extern int QUEUE_CDSLight;
extern String QUEUE_StringOne;
extern String QUEUE_StringTwo;

void ProximitySensorClass::init()
{


}

void ProximitySensorClass::init( int inPin, int outPin, int delayForReflectionWaveInMS)
{
	m_inPin = inPin;
	m_outPin = outPin;
	m_delayForReflectionWaveInMS = delayForReflectionWaveInMS;

	pinMode(m_inPin, INPUT);
	pinMode(m_outPin, OUTPUT);
}

bool ProximitySensorClass::sense()
{
	digitalWrite(m_outPin, HIGH);
	delayMicroseconds(m_delayForReflectionWaveInMS);
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

ProximitySensorClass ProximitySensor;

