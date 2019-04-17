// MessageQueue.h

#ifndef _MESSAGEQUEUE_h
#define _MESSAGEQUEUE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Message.h"

class MessageQueue
{
private:
	Message** buffer_;
	const int size_;
	int head_;
	int tail_;

public:
	MessageQueue(int size);
	~MessageQueue();
	int next(int cur);
	bool put(Message* pMessage);
	Message* get();
};

#endif

