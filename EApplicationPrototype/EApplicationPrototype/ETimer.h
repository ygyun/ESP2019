// ETimer.h

#ifndef _ETIMER_h
#define _ETIMER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "EComponent.h"

class ETimer: public EComponent
{
public:
	enum EState{
		eStart,
		eStop,
		ePause,
		eNumStates
	};
	unsigned int preTime;
	unsigned int curTime;
	void processAMessage(EMessage* pMessage) {
		if (pMessage->getType() == ETimer::eStart) {
			preTime = curTime;
			curTime = millis();

			// to send message self too
		}
	}
};

#endif

