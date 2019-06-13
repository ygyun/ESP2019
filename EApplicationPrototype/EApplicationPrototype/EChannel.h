// Channel.h

#ifndef _ECHANNEL_h
#define _ECHANNEL_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "EGlobal.h"

class EChannel
{
protected:
	int pinNum;

public:
	EChannel(int pinNum) : pinNum(pinNum) {}
	~EChannel() {}
	virtual void initialize() = 0;
	virtual void finalize() =0;
	virtual int read() =0;
	virtual void write(int toWrite) =0;
};

#endif
