// EDummySender.h

#ifndef _EDUMMYSENDER_h
#define _EDUMMYSENDER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "EComponent.h"

class EDummySender : public EComponent
{
public:
	enum EMessageType {
		eWakeUp,
		eNumMessageTypes
	};
	enum EState {
		eReady,
		eRunning,
		eStopped,
		eNumStates
	};
private:
	EState eState;
public:
	EDummySender() {
		this->eState = EState::eStopped;
	}
	~EDummySender() {}
	void initialize() {}
	void finalize() {}
	void generateAMessage() {
		if (this->eState == EState::eRunning) {
			for (EComponent *pComponent : this->pReceivers) {
				ELOG(ELOG_DEBUG, "EDummySender is GENerating a msg.", "");
				pComponent->addAReceiverMessage(0, pComponent);
			}
			this->eState = EState::eStopped;
		}
	}
	void processAMessage(EMessage* pMessage) {
		ELOG(ELOG_DEBUG, "EDummySender is PROcessing a msg.", "");
		this->eState = EState::eRunning;
	}
};

#endif