// ServoMotor.h

#ifndef _SERVOMOTOR_h
#define _SERVOMOTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Servo.h>
#include "Actuator.h"

class ServoMotor : public Actuator
{
private:
	Servo m_servoMotor;
	int m_attchPin;
	int m_prevAngle;
	bool m_triggered; 
public:
	ServoMotor(int attachPin);
	void init();
	void start();
	bool wait();
	bool slicedWait();
};

#endif

