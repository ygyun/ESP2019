// Illuminant.h

#ifndef _ILLUMINANT_h
#define _ILLUMINANT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Sensor.h"

class Illuminant : public Sensor
{
private:
	int m_inPin;
	int m_CDSLight;

public:
	Illuminant(int inPin);
	void init();
	void start();
	bool wait();
};
#endif

