// PiezoSpeaker.h

#ifndef _PIEZOSPEAKER_h
#define _PIEZOSPEAKER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Actuator.h"

class PiezoSpeaker : public Actuator
{
private:
	int m_outPin;
	long m_intervalBTNotes;
	int m_prevIndex;
	bool m_triggered;
public:
	PiezoSpeaker(int outPin, long intevalBTNotes);
	void init();
	void start();
	bool wait();
	bool slicedWait();
};
#endif

