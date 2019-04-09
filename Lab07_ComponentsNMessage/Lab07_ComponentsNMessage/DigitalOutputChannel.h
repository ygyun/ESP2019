// DigitalOutputChannel.h

#ifndef _DIGITALOUTPUTCHANNEL_h
#define _DIGITALOUTPUTCHANNEL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Channel.h"

class DigitalOutputChannel: public Channel
{
public:
	DigitalOutputChannel(int pinNum): Channel(pinNum) {}

	~DigitalOutputChannel() {}

	void initialize() {
		pinMode(Channel::pinNum_, OUTPUT);
	}

	void finalize() {}

	int read() {
		return 0;
	}

	void write(int toWrite) {
		digitalWrite(Channel::pinNum_, toWrite);
	}
};

#endif

