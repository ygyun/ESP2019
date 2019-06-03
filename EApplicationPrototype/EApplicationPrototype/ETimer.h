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
	enum EState {
		Timeout,
		eStart,
		eStop,
		ePause,
		eNumStates
	};
private:
	unsigned long preTime;
	unsigned long curTime;
public:
	ETimer() {}
	~ETimer() {}
	void initialize() {
		this->preTime = millis();
	}
	void finalize() {}
	void generateAMessage() {
		this->curTime = millis();
		unsigned long diff = this->curTime - this->preTime;
		if (diff >= TIMER_TIMEOUT) {
			this->preTime = this->curTime;
			ELOG(ELOG_INFO, "Time diff: ", diff);
			ELOG(ELOG_INFO, "ETimer is GENerating a msg.", "");
			this->addATargetMessage(0);
		}
	}
	void processAMessage(EMessage* pMessage) {}
};

#endif

