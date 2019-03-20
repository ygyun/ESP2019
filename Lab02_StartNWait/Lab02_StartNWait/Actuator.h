// Actuator.h

#ifndef _ACTUATOR_h
#define _ACTUATOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Device.h"

class Actuator : public Device
{
 public:
	 Actuator();
	 virtual void init();
	 virtual void start();
	 virtual bool wait();
};
#endif

