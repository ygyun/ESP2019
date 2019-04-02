// PWMInputChannel.h

#ifndef _PWMINPUTCHANNEL_h
#define _PWMINPUTCHANNEL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Channel.h"

class PWMInputChannel : public Channel
{
public:
	PWMInputChannel(int pinNum) : Channel(pinNum)
	{}

	~PWMInputChannel() {}

	void initialize() {
		pinMode(Channel::pinNum_, INPUT);
	}

	void finalize() {}

	int read() {
		return analogRead(Channel::pinNum_);
	}

	void write(int toWrite) {}
};

#endif

