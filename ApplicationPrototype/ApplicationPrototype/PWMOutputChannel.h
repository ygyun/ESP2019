// PWMOutputChannel.h

#ifndef _PWMOUTPUTCHANNEL_h
#define _PWMOUTPUTCHANNEL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Channel.h"

class PWMOutputChannel: public Channel
{
public:
	PWMOutputChannel(int pinNum): Channel(pinNum) {}

	~PWMOutputChannel() {}

	void initialize() {
		pinMode(Channel::pinNum_, OUTPUT);
	}

	void finalize() {}

	int read() {
		return 0;	// This fuction shouldn't be called
	}

	void write(int toWrite) {
		analogWrite(Channel::pinNum_, toWrite);
	}
};

#endif

