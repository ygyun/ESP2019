// Component.h

#ifndef _COMPONENT_h
#define _COMPONENT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Globals.h"
#include "Message.h"
#include "MessageQueue.h"

class Component
{
public:
	enum EMessageType {
		eLightState,
		eDistanceState,
		eNumMessageTypes
	};
	MessageQueue* pMessageQueue_;
	Component* pSourceComponent_;
	Component* pTargetComponent_;
public:
	Component() :
		pMessageQueue_(new MessageQueue(MJUC_SIZE_OF_MESSAGE_QUEUE)),
		pSourceComponent_(NULL),
		pTargetComponent_(NULL) {}

	~Component() {
		delete this->pMessageQueue_;
	}

	void associateWithASourceComponent(Component* pSourceComponent) {
		this->pSourceComponent_ = pSourceComponent;
		this->pTargetComponent_ = this;
	}

	void associateWithATargetComponent(Component* pTargetComponent) {
		this->pTargetComponent_ = pTargetComponent;
		this->pSourceComponent_ = this;
	}

	void createAMessage(int eMessageType, int iValue) {
		Message::UValue uArgument;
		uArgument.iValue = iValue;

		Message* pMsg = new Message(eMessageType, this->pSourceComponent_, this->pTargetComponent_, uArgument);
		this->pMessageQueue_->put(pMsg);
	}

	virtual void initialize()=0;
	virtual void finalize()=0;
	virtual void generateMessages()=0;
	virtual void processAMessage(Message* pMessage)=0;
};

#endif