// ServoMotor.h

#ifndef _SERVOMOTOR_h
#define _SERVOMOTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Motor.h"
#include <Servo.h>

class ServoMotorClass : public MotorClass
{
 protected:
	 Servo* m_ServoMotor;
	 int m_attchPin;

 public:
	 void init();
	 void init(int attachPin);
	 bool process();
	 bool operate();
};

extern ServoMotorClass ServoMotor;

#endif

