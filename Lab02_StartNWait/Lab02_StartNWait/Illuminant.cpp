// 
// 
// 

#include "Illuminant.h"

extern int QUEUE_DistanceInCM;
extern int QUEUE_CDSLight;
extern String QUEUE_StringOne;
extern String QUEUE_StringTwo;

extern int cdsLightVauleForDayNNight;
extern int shortDistance;
extern int middleDistance;
extern int longDistance;
extern int maxAngleOfServoMotor;

Illuminant::Illuminant(int inPin) :
	m_inPin(inPin)
{	
}

void Illuminant::init()
{
	m_CDSLight = 0;
}

void Illuminant::start()
{

}

bool Illuminant::wait()
{
	m_CDSLight = analogRead(m_inPin);
	QUEUE_CDSLight = m_CDSLight;
	QUEUE_StringOne = "Light: ";
	QUEUE_StringOne += QUEUE_CDSLight;

	return true;
}

