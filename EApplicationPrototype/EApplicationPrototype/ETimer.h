// ETimer.h

#ifndef _ETIMER_h
#define _ETIMER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "EComponent.h"


class ETimer : public EComponent
{
public:
	enum EMessageType {
		eWakeUp,
		eNumMessageTypes
	};
	enum EState {
		Timeout,
		eStart,
		eStop,
		ePause,
		eNumStates
	};
private:
	unsigned long timeout;
	unsigned long preTime;
	unsigned long curTime;
public:
	ETimer(unsigned int timeout = TIMER_TIMEOUT): timeout(timeout) {}
	~ETimer() {}
	void initialize() {
		this->preTime = millis();
	}
	void finalize() {}
	void generateAMessage() {
		this->curTime = millis();
		unsigned long diff = this->curTime - this->preTime;
		if (diff >= this->timeout) {
			this->preTime = this->curTime;
			ELOG(ELOG_INFO, "Timer: ", diff);
			ELOG(ELOG_DEBUG, "ETimer is GENerating a msg.", "");
			this->addATargetMessage(EMessageType::eWakeUp);
		}
	}
	void processAMessage(EMessage* pMessage) {}
};

#endif

