// Device.h

#ifndef _DEVICE_h
#define _DEVICE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Device
{
 public:
	Device();
	virtual void init();
	virtual void start();
	virtual bool wait();
};

#endif

