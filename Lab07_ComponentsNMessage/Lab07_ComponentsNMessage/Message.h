// Message.h

#ifndef _MESSAGE_h
#define _MESSAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Component.h"

class Message
{
public:
	enum EMessageType {
		eNumMessageTypes
	};
private:
	static int iCount_;
	int messageID_;
	int messageType_;
	Component* pTargetComponent_;
	Component* pSourceComponent_;
	void* pArgument_;
public:
	Message(EMessageType messageType, Component* pTargetComponent, Component* pSourceComponent, void* pArgument);
	~Message();
	void* operator new (size_t size);
	void operator delete (void* pointerToDelete);
};

#endif