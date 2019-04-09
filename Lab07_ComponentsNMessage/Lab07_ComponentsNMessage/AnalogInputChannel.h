// AnalogInputChannel.h

#ifndef _ANALOGINPUTCHANNEL_h
#define _ANALOGINPUTCHANNEL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Channel.h"

class AnalogInputChannel: public Channel
{
public:
	AnalogInputChannel(int pinNum): Channel(pinNum) {}

	~AnalogInputChannel() {}

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

