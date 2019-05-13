// EComponent.h

#ifndef _ECOMPONENT_h
#define _ECOMPONENT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "EQueue.h"
#include "EMessage.h"

class EComponent
{
private:
	int UID_;	// will be expand to URL...
	static int classID_;
	EQueue<EMessage*>* pMessageQueue_;
	EComponent* pReceivers_[10];
	int receiverIndex_ = 0;
	EComponent* pTargets_[10];
	int targetIndex_ = 0;

protected:
	virtual void processAMessage(EMessage* pMessage) = 0;

	void addMessage(EMessage* pMessage) {
		this->pMessageQueue_->enqueue(pMessage);
	}

	void addAReceiverMessage(unsigned int eventType, EComponent* pReceiver, int iArg = 0, void* pArg = NULL) {
		EMessage* pMessage = new EMessage(eventType, pReceiver, iArg, pArg);
		this->addMessage(pMessage);
	}

	void addATargetMessage(unsigned int eventType, int iArg = 0, void* pArg = NULL) {
		for (EComponent* pComponent : pTargets_) {
			pComponent->addAReceiverMessage(eventType, pComponent, iArg, pArg);
		}
	}

public:
	EComponent() {}

	virtual ~EComponent() {}

	void setPMessageQueue(EQueue<EMessage*>* pMessageQueue) {
		this->pMessageQueue_ = pMessageQueue;
	}

	void processAMessageCaller(EMessage* pMessage) {
		// pre- To do
		this->processAMessage(pMessage);
		// post- To do
	}

	void associateAReceiver(EComponent* pReceiver) {
		this->pReceivers_[receiverIndex_++] = pReceiver;
	}

	void associateATarget(EComponent* pTarget) {
		this->pTargets_[targetIndex_++] = pTarget;
	}
};

#endif