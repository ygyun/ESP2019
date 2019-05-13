// EQueue.h

#ifndef _EQUEUE_h
#define _EQUEUE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

template<typename Element, int size=32>
class EQueue
{
private:
	Element buffer_[size];
	int head_;
	int tail_;
	int count_; // usage etc...

public:
	EQueue() {
		this->head_ = 0;
		this->tail_ = 0;
	}

	~EQueue() {}

inline int next(int cur) {
		return (cur + 1) % size;
	}

	bool enqueue(Element element) {
		if (this->head_ == next(this->tail_)) {
			return false;
		}
		this->buffer_[this->tail_] = element;
		this->tail_ = next(this->tail_);
		return true;
	}

	Element dequeue() {
		if (this->head_ == this->tail_) {
			return NULL;
		}
		Element return_value = this->buffer_[this->head_];
		this->head_ = next(this->head_);
		return return_value;
	}
};

#endif

