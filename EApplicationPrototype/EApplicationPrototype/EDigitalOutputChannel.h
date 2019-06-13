// DigitalOutputChannel.h

#ifndef _DIGITALOUTPUTCHANNEL_h
#define _DIGITALOUTPUTCHANNEL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "EChannel.h"

class EDigitalOutputChannel: public EChannel
{
public:
	EDigitalOutputChannel(int pinNum): EChannel(pinNum) {}
	~EDigitalOutputChannel() {}
	void initialize() {	pinMode(EChannel::pinNum, OUTPUT); }
	void finalize() {}
	int read() { return 0; }
	void write(int toWrite) { digitalWrite(EChannel::pinNum, toWrite); }
};

#endif

