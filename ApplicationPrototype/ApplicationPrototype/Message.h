// Message.h

#ifndef _MESSAGE_h
#define _MESSAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Component;

class Message
{
public:
	typedef union _UValue {
		int iValue;
		long lValue;
		double dValue;
		void* pVoid;
	} UValue;

public:
	static int iCount_;
	int messageID_;
	int messageType_;
	Component* pSourceComponent_;
	Component* pTargetComponent_;
	UValue uArgument_;

public:
	Message(int messageType, Component* pSourceComponent, Component* pTargetComponent, UValue uArgument);
	~Message();
	void* operator new (size_t size);
	void operator delete (void* pointerToDelete);
};

#endif