// 
// 
// 

#include "ServoMotor.h"

extern int QUEUE_DistanceInCM;
extern int QUEUE_CDSLight;
extern String QUEUE_StringOne;
extern String QUEUE_StringTwo;

extern int cdsLightVauleForDayNNight;
extern int shortDistance;
extern int middleDistance;
extern int longDistance;
extern int maxAngleOfServoMotor;

ServoMotor::ServoMotor(int attachPin) :
	m_attchPin(attachPin), m_servoMotor(Servo())
{	
}

void ServoMotor::init()
{
	m_servoMotor.attach(m_attchPin);
	m_prevAngle = 0;
	m_triggered = false;
}

void ServoMotor::start()
{

}

bool ServoMotor::wait()
{
	if (QUEUE_DistanceInCM < shortDistance)
	{
		for (int i = 0; i < maxAngleOfServoMotor; ++i)
		{
			m_servoMotor.write(i);
			delay(1);
		}
		delay(100);

		m_servoMotor.write(0);

		return true;
	}
	else
		return false;
}

bool ServoMotor::slicedWait()
{
	if (!m_triggered)
	{
		if (QUEUE_DistanceInCM < shortDistance)
		{
			m_triggered = true;
		}

	}

	if (m_triggered)
	{
		int i = m_prevAngle;
		int j = 0;
		for ( ; (j<10) && (i< maxAngleOfServoMotor); i++, j++)
		{
			m_servoMotor.write(i);
			delay(1);
		}

		m_prevAngle += j;
		if (m_prevAngle >= maxAngleOfServoMotor)
		{
			m_servoMotor.write(0);
			m_prevAngle = 0;
			m_triggered = false;
		}

		return true;
	}
	else
		return false;
}