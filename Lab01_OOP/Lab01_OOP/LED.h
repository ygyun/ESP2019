// LED.h

#ifndef _LED_h
#define _LED_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Actuator.h"

class LEDClass : public ActuatorClass
{
 protected:


 public:
	virtual void init();
	virtual bool process();
	virtual bool operate();
};

extern LEDClass LED;

#endif

