// ActSensor.h

#ifndef _ACTSENSOR_h
#define _ACTSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Device.h"

class ActSensor : public Device
{
 public:
	 ActSensor();
	 virtual void init();
	 virtual void start();
	 virtual bool wait();
};

#endif

