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

public:
	Channel(int pinNum) : pinNum_(pinNum)
	{}

	~Channel() {}

	virtual void initialize();
	virtual void finalize();
	virtual int read();
	virtual void write(int toWrite);

	int getPinNum() {
		return this->pinNum_;
	}
};

#endif
