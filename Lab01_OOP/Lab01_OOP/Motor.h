// Motor.h

#ifndef _MOTOR_h
#define _MOTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Actuator.h"

class MotorClass : public ActuatorClass
{
 protected:


 public:
	 virtual void init();
	 virtual bool process();
	 virtual bool operate();
};

extern MotorClass Motor;

#endif

