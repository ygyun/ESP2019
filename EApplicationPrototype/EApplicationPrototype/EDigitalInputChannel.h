// DigitalInputChannel.h

#ifndef _EDIGITALINPUTCHANNEL_h
#define _EDIGITALINPUTCHANNEL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "EChannel.h"

class EDigitalInputChannel: public EChannel
{
public:
	EDigitalInputChannel(int pinNum): EChannel(pinNum) {}
	~EDigitalInputChannel() {}
	void initialize() {	pinMode(EChannel::pinNum, INPUT); }
	void finalize() {}
	int read() { return digitalRead(EChannel::pinNum); }
	void write(int toWrite) {}
};

#endif

