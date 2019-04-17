// Scheduler.h

#ifndef _SCHEDULER_h
#define _SCHEDULER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Component.h"
#include "Illuminant.h"
#include "Proximity.h"
#include "LED.h"
#include "LEDManagerWithLIghtNDistance.h"

class Scheduler: public Component
{
private:
	Component* pSensorComponents_[2];
	Component* pActuatorComponents_[1];

	Illuminant* pIlluminant;
	Proximity* pProximity;
	LED* pLED;

	LEDManagerWithLIghtNDistance* pLEDManagerWithLIghtNDistance;

public:
	Scheduler();
	~Scheduler();
	void initialize();
	void finalize();
	void run();
	void generateMessages();
	void processAMessage(Message* pMessage);
};

#endif
