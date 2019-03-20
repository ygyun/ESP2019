// Proximity.h

#ifndef _PROXIMITY_h
#define _PROXIMITY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "ActSensor.h"

class Proximity : public ActSensor
{
private:
	int m_inPin;
	int m_outPin;
	int m_retensionTimeForFiringWaveInMS;
	long m_reflectionTimeInMS;
public:
	Proximity(int inPin, int outPin, int retensionTimeForFiringWaveInMS);
	void init();
	void start();
	bool wait();
};

#endif

