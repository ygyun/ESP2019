// DigitalInputChannel.h

#ifndef _DIGITALINPUTCHANNEL_h
#define _DIGITALINPUTCHANNEL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Channel.h"

class DigitalInputChannel : public Channel
{
public:
	DigitalInputChannel(int pinNum) : Channel(pinNum)
	{}

	~DigitalInputChannel() {}

	void initialize() {
		pinMode(Channel::pinNum_, INPUT);
	}

	void finalize() {}

	int read() {
		return digitalRead(Channel::pinNum_);
	}

	void write(int toWrite) {}
};

#endif

