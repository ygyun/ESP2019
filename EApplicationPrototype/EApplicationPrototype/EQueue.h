// EQueue.h

#ifndef _EQUEUE_h
#define _EQUEUE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "EGlobal.h"

template<typename Element, int size = DEFAULT_SIZE_OF_EQUEUE>
class EQueue
{
private:
	Element buffer[size];
	unsigned int head;
	unsigned int tail;
	unsigned int count;

public:
	EQueue() {
		this->head = 0;
		this->tail = 0;
		this->count = 0;
	}

	~EQueue() {}

	int next(int cur) {
		return (cur + 1) % size;
	}

	bool enqueue(Element element) {
		ELOG(ELOG_ALL, "EQueue::enqueue()", "");
		if (this->head == next(this->tail)) {
			ELOG(ELOG_ERROR, "EQueue is full.", "");
			return false;
		}
		this->buffer[this->tail] = element;
		this->tail = next(this->tail);
		(this->count)++;
		return true;
	}

	Element dequeue() {
		if (this->head == this->tail) {
			return NULL;
		}
		Element returnValue = this->buffer[this->head];
		this->head = next(this->head);
		(this->count)--;
		return returnValue;
	}

	unsigned int getCount() { return this->count;}

	void clear() {
		this->head = 0;
		this->tail = 0;
		this->count = 0;
	}
};

#endif