// RGBLED.h

#ifndef _RGBLED_h
#define _RGBLED_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "LED.h"

#define _DELAY_FOR_RGBLED_IN_MS 100

class RGBLEDClass : public LEDClass
{
 protected:
	 int m_RPin;
	 int m_GPin;
	 int m_BPin;
	 int m_RValue;
	 int m_GValue;
	 int m_BValue;
	 int m_delayForRGBLEDInMS = _DELAY_FOR_RGBLED_IN_MS;

 public:
	void init();
	void init(int RPin, int GPin, int BPin);
	bool process();
	bool operate();
};

extern RGBLEDClass RGBLED;

#endif

