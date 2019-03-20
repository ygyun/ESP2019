// 
// 
// 

#include "ServoMotor.h"

extern int QUEUE_DistanceInCM;
extern int QUEUE_CDSLight;
extern String QUEUE_StringOne;
extern String QUEUE_StringTwo;

void ServoMotorClass::init()
{


}

void ServoMotorClass::init(int attachPin)
{
	m_ServoMotor = new Servo();
	m_attchPin = attachPin;
	m_ServoMotor->attach(m_attchPin);
}

bool ServoMotorClass::process()
{
	if (QUEUE_DistanceInCM < 5)
		return true;
	else
		return false;
}

bool ServoMotorClass::operate()
{
	for (int i = 0; i < 90; ++i)
	{
		m_ServoMotor->write(i);
		delay(1);
	}
	delay(100);

	m_ServoMotor->write(0);

	return true;	
}

ServoMotorClass ServoMotor;

