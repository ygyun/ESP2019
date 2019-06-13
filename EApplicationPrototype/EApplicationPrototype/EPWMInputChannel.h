// PWMInputChannel.h

#ifndef _PWMINPUTCHANNEL_h
#define _PWMINPUTCHANNEL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "EChannel.h"

class EPWMInputChannel: public EChannel
{
public:
	EPWMInputChannel(int pinNum): EChannel(pinNum) {}
	~EPWMInputChannel() {}
	void initialize() {	pinMode(EChannel::pinNum, INPUT); }
	void finalize() {}
	int read() { return analogRead(EChannel::pinNum); }
	void write(int toWrite) {}
};

#endif

