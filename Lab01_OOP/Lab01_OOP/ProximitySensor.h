// ProximitySensor.h

#ifndef _PROXIMITYSENSOR_h
#define _PROXIMITYSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Sensor.h"

class ProximitySensorClass : public SensorClass
{
 protected:
	 int m_inPin;
	 int m_outPin;
	 int m_delayForReflectionWaveInMS;
	 long m_reflectionTimeInMS;

 public:
	void init();
	void init(int inPin, int outPin, int delayForReflectionWaveInMS);
	bool sense();
};

extern ProximitySensorClass ProximitySensor;


#endif

