// Actuator.h

#ifndef _ACTUATOR_h
#define _ACTUATOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class ActuatorClass
{
 protected:


 public:
	virtual void init();
	virtual bool process();
	virtual bool operate();
};

extern ActuatorClass Actuator;

#endif

