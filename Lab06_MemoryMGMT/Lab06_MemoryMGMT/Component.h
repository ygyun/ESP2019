// Component.h

#ifndef _COMPONENT_h
#define _COMPONENT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Component
{
public:
	virtual void initialize();
	virtual void finalize();
	virtual void run();
	virtual void start();
	virtual bool wait();
	virtual void sense();
	virtual void process();
	virtual void actuate();
};

#endif