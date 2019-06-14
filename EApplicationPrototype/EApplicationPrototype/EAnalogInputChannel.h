// AnalogInputChannel.h

#ifndef _EANALOGINPUTCHANNEL_h
#define _EANALOGINPUTCHANNEL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "EChannel.h"

class EAnalogInputChannel: public EChannel
{
public:
	EAnalogInputChannel(int pinNum): EChannel(pinNum) {}
	~EAnalogInputChannel() {}
	void initialize() { pinMode(EChannel::pinNum, INPUT); }
	void finalize() {}
	int read() { return analogRead(EChannel::pinNum); }
	void write(int toWrite) {}
};

#endif

