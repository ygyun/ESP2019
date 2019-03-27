// Domain.h

#ifndef _DOMAIN_h
#define _DOMAIN_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class Domain
{
public:
	virtual void initialize();
	virtual void finalize();
	virtual void process();
	virtual void actuate();
	virtual void run();
};

#endif

