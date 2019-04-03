// TRSensor.h

#ifndef _TRSENSOR_h
#define _TRSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Sensor.h"

class TRSensor: public Sensor
{
public:
	virtual void initialize();
	virtual void finalize();
	virtual void sense();
	virtual int getState();
};

#endif

