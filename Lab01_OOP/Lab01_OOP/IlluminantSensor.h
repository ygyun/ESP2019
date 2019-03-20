// IlluminantSensor.h

#ifndef _ILLUMINANTSENSOR_h
#define _ILLUMINANTSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Sensor.h"

class IlluminantSensorClass : public SensorClass
{
 protected:
	 int m_inPin;
	 int m_CDSLight;

 public:
	void init();
	void init(int inPin);
	bool sense();
};

extern IlluminantSensorClass IlluminantSensor;


#endif

