// Message.h

#ifndef _MESSAGE_h
#define _MESSAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Globals.h"

class Message
{
private:
	int id_;
	int state_;
public:
	Message(int id, int state);
	~Message();
	void* operator new (size_t size);
	void operator delete (void* pointerToDelete);
};

#endif

