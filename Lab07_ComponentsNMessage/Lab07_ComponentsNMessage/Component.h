// Component.h

#ifndef _COMPONENT_h
#define _COMPONENT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Channel.h"
class Message;

class Component
{
public:
	Component() {}
	~Component() {}
	virtual void initialize();
	virtual void finalize();
	virtual void generateMessage();
	virtual void processMessage(Message* pMessage);
};

#endif