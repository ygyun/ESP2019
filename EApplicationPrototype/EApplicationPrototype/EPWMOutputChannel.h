// PWMOutputChannel.h

#ifndef _PWMOUTPUTCHANNEL_h
#define _PWMOUTPUTCHANNEL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "EChannel.h"

class EPWMOutputChannel: public EChannel
{
public:
	EPWMOutputChannel(int pinNum): EChannel(pinNum) {}
	~EPWMOutputChannel() {}
	void initialize() { pinMode(EChannel::pinNum, OUTPUT); }
	void finalize() {}
	int read() { return 0; }
	void write(int toWrite) { analogWrite(EChannel::pinNum, toWrite); }
};

#endif

