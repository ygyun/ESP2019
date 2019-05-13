// EScheduler.h

#ifndef _ESCHEDULER_h
#define _ESCHEDULER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "EGlobal.h"
#include "EComponent.h"

//TypeID<EScheduler> tidEScheduler;

class EScheduler : public EComponent
{
public:
	enum EMessageType {
		eRun,
		eStop,
		ePause,
		eNumMessageTypes
	};
	enum EState {
		eRunning,
		eStopped,
		eNumStates
	};
private:
	EQueue<EMessage*> eMessageQueue;
	EState eState;

public:
	EScheduler() { this->eState = EState::eRunning; }
	~EScheduler() {}
	void initialize() {}
	void finalize() {}
	void processAMessage(EMessage* pMessage) {
		switch (pMessage->getType()) {
		case eStop:
			this->eState = eStopped; break;
		}
	}

	void run() {
//		addAReceiverMessage(to timer);
		while (this->eState == EState::eRunning) {	// State flag
			EMessage* pEMessage = eMessageQueue.dequeue();
			if (NULL == pEMessage) {
				delay(1000); // 1ms
			}
			else {
				pEMessage->getPTarget()->processAMessageCaller(pEMessage);
			}
		}
		this->finalize();
	}
};

#endif

