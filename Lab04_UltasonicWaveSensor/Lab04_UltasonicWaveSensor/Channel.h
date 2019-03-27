// Channel.h

#ifndef _CHANNEL_h
#define _CHANNEL_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class Channel
{
protected:
	int pinNum_;
	int data_;

public:
	Channel(int pinNum) : pinNum_(pinNum)
	{}

	~Channel() {}

	virtual void initialize();
	virtual void finalize();
	virtual int read();
	virtual void write();

	int getPinNum() {
		return this->pinNum_;
	}

	int getData() {
		return this->data_;
	}

	void setData(int data) {
		this->data_ = data;
	}
};

#endif
