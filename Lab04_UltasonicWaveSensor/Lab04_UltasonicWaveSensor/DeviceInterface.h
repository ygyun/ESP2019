// DeviceInterface.h

#ifndef _DEVICEINTERFACE_h
#define _DEVICEINTERFACE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class DeviceInterface
{
public:
	virtual void initialize();
	virtual void finalize();
	virtual void start();
	virtual bool wait();
};

#endif

