// Sensor.h

#ifndef _SENSOR_h
#define _SENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Device.h"

class Sensor : public Device
{
 public:
	 Sensor();
	 virtual void init();
	 virtual void start();
	 virtual bool wait();
};
#endif

