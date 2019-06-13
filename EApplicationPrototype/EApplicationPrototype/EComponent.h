// EComponent.h

#ifndef _ECOMPONENT_h
#define _ECOMPONENT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "EGlobal.h"
#include "EQueue.h"
#include "EArray.h"
#include "EMessage.h"

class EComponent
{
protected:
	int UID;
	EQueue<EMessage*>* pMessageQueue;
	EArray<EComponent*> pReceivers;
	EArray<EComponent*> pTargets;

	void addMessage(EMessage* pMessage) {
		this->pMessageQueue->enqueue(pMessage);
	}

public:
	EComponent() {}
	virtual ~EComponent() {}
	virtual void initialize() = 0;
	virtual void finalize() = 0;
	virtual void generateAMessage() = 0;
	virtual void processAMessage(EMessage* pMessage) = 0;

	void setPMessageQueue(EQueue<EMessage*>* pMessageQueue) {
		this->pMessageQueue = pMessageQueue;
	}

	void associateAReceiver(EComponent* pReceiver) {
		this->pReceivers.add(pReceiver);
	}

	void associateATarget(EComponent* pTarget) {
		this->pTargets.add(pTarget);
	}

	void addAReceiverMessage(unsigned int eventType, EComponent* pReceiver, int iArg = 0, void* pArg = NULL) {
		EMessage* pMessage = new EMessage(eventType, pReceiver, iArg, pArg);
		this->addMessage(pMessage);
	}

	void addATargetMessage(unsigned int eventType, int iArg = 0, void* pArg = NULL) {
		ELOG(ELOG_ALL, "EComponent::addATargetMessage()", "");
		ELOG(ELOG_ALL, "pTargets count: ", this->pTargets.getCount());
		for (EComponent* pComponent : this->pTargets) {
			this->addAReceiverMessage(eventType, pComponent, iArg, pArg);
		}
	}

	void processAMessageCaller(EMessage* pMessage) {
		// pre To do
		this->processAMessage(pMessage);
		delete pMessage;
		// post To do
	}
};

#endif