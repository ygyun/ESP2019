// Sensor.h

#ifndef _SENSOR_h
#define _SENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class SensorClass
{
 protected:


 public:
	virtual void init();
	virtual bool sense();
};

extern SensorClass Sensor;

#endif

