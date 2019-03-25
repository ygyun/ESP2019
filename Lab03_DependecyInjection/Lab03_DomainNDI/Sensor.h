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
	Sensor() {}
	~Sensor() {}

	virtual void initialize();
	virtual void finalize();
	virtual void start();
	virtual bool wait();
};

#endif