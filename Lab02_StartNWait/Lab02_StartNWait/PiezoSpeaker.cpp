// 
// 
// 

#include "PiezoSpeaker.h"

int melody[] = { 262,294,330,349,392,440,494,523 };
int len[] = { 100,100,100,100,100,100,100,100 };

extern int QUEUE_DistanceInCM;
extern int QUEUE_CDSLight;
extern String QUEUE_StringOne;
extern String QUEUE_StringTwo;

extern int cdsLightVauleForDayNNight;
extern int shortDistance;
extern int middleDistance;
extern int longDistance;
extern int maxAngleOfServoMotor;

PiezoSpeaker::PiezoSpeaker(int outPin, long intervalBTNotes) :
	m_outPin(outPin), m_intervalBTNotes(intervalBTNotes)
{
}

void PiezoSpeaker::init()
{
	m_prevIndex = 0;
	m_triggered = false;
}

void PiezoSpeaker::start()
{

}

bool PiezoSpeaker::wait()
{
	if (QUEUE_DistanceInCM < middleDistance)
	{
		for (int i = 0; i < 8; i++)
		{
			tone(m_outPin, melody[i], len[i]);
			delay(m_intervalBTNotes);
			noTone(m_outPin);
		}
		
		return true;
	}
	else
		return false;
}

bool PiezoSpeaker::slicedWait()
{
	if (!m_triggered)
	{
		if (QUEUE_DistanceInCM < middleDistance)
		{
			m_triggered = true;
		}

	}

	if (m_triggered)
	{
		noTone(m_outPin);
		tone(m_outPin, melody[m_prevIndex], len[m_prevIndex]);

		m_prevIndex++;
		if (m_prevIndex == 8)
		{
			m_prevIndex = 0;
			m_triggered = false;
		}

		return true;
	}
	else
		return false;
}