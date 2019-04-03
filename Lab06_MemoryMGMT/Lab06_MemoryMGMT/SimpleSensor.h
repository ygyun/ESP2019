// SimpleSensor.h

#ifndef _SIMPLESENSOR_h
#define _SIMPLESENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Sensor.h"

class SimpleSensor: public Sensor
{
public:
	virtual void initialize();
	virtual void finalize();
	virtual void sense();
	virtual int getState();
};

#endif

