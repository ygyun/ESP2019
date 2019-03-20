// RGBLED.h

#ifndef _RGBLED_h
#define _RGBLED_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Actuator.h"

class RGBLED : public Actuator
{
private:
	int m_RPin;
	int m_GPin;
	int m_BPin;
	int m_RValue;
	int m_GValue;
	int m_BValue;
public:
	RGBLED(int RPin, int GPin, int BPin);
	void init();
	void start();
	bool wait();
};
#endif

