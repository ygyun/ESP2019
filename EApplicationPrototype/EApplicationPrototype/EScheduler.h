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
		eReady,
		eRunning,
		eStopped,
		eNumStates
	};
private:
	EArray<EComponent*> pMessageGeneratingComponents;
	EQueue<EMessage*> messageQueue;
	EState eState;

public:
	EScheduler() {
		this->eState = EState::eReady;
	}
	~EScheduler() {}
	void initialize() {}
	void finalize() {}
	void generateAMessage() {}
	void processAMessage(EMessage* pMessage) {
		switch (pMessage->getType()) {
		case EMessageType::eStop:
			this->eState = EState::eStopped; break;
		}
	}

	EQueue<EMessage*>& getMessageQueue() {
		return this->messageQueue;
	}

	void addAMessageGeneratingComponent(EComponent* pComponent) {
		this->pMessageGeneratingComponents.add(pComponent);
	}

	void run() {
		ELOG(ELOG_DEBUG, "EScheduler::run()", "");
		while (this->eState == EState::eReady) {
			// Sensing
			for (EComponent* pComponent : this->pMessageGeneratingComponents) {
				pComponent->generateAMessage();
			}
			ELOG(ELOG_ALL, "Queue size: ", messageQueue.getCount());
			// Actuating
			EMessage* pEMessage = this->messageQueue.dequeue();
			if (NULL != pEMessage) {
				ELOG(ELOG_ALL, "messageQueue.dequeue()", "");
				pEMessage->getPTarget()->processAMessageCaller(pEMessage);
				ELOG(ELOG_ALL, "processed message", "");
			}
		}
	}
};

#endif