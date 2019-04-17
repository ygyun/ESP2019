// 
// 
// 

#include "MessageQueue.h"

MessageQueue::MessageQueue(int size) : size_(size) {
	this->buffer_ = new Message*[size];
	this->head_ = 0;
	this->tail_ = 0;
}

MessageQueue::~MessageQueue() {
	delete[] this->buffer_;
}

int MessageQueue::next(int cur) {
	return (cur + 1) % this->size_;
}

bool MessageQueue::put(Message* pMessage) {
	if (this->head_ == next(this->tail_)) {
		return false;
	}
	this->buffer_[this->tail_] = pMessage;
	this->tail_ = next(this->tail_);
	return true;
}

Message* MessageQueue::get() {
	if (this->head_ == this->tail_) {
		return NULL;
	}
	Message* pReturn = this->buffer_[this->head_];
	this->head_ = next(this->head_);
	return pReturn;
}