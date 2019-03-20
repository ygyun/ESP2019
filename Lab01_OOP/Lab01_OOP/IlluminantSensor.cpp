// 
// 
// 

#include "IlluminantSensor.h"
extern int QUEUE_DistanceInCM;
extern int QUEUE_CDSLight;
extern String QUEUE_StringOne;
extern String QUEUE_StringTwo;

void IlluminantSensorClass::init()
{


}

void IlluminantSensorClass::init(int inPin)
{
	m_inPin = inPin;
}

bool IlluminantSensorClass::sense()
{
	m_CDSLight = analogRead(m_inPin);
	QUEUE_CDSLight = m_CDSLight;
	QUEUE_StringOne = "Light: ";
	QUEUE_StringOne += QUEUE_CDSLight;
	
	return true;
}

IlluminantSensorClass IlluminantSensor;

