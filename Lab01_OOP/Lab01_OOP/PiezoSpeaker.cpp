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

void PiezoSpeakerClass::init()
{


}

void PiezoSpeakerClass::init(int outPin)
{
	m_outPin = outPin;
}

bool PiezoSpeakerClass::process()
{
	if (QUEUE_DistanceInCM < 10)
		return true;
	else
		return false;
}

bool PiezoSpeakerClass::operate()
{
	for (int i = 0; i < 8; i++)
	{
		tone(m_outPin, melody[i], len[i]);
		delay(m_delayBTNotes);
		noTone(m_outPin);
	}

	return true;
}

PiezoSpeakerClass PiezoSpeaker;

