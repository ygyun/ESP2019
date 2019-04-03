// Sensor.h

#ifndef _SENSOR_h
#define _SENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Sensor
{
public:
	virtual void initialize();
	virtual void finalize();
	virtual void sense();
	virtual int getState();
};

#endif

