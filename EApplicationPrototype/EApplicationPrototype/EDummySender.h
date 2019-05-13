// EDummySender.h

#ifndef _EDUMMYSENDER_h
#define _EDUMMYSENDER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "EComponent.h"

class EDummySender: public EComponent
{
private:
//	main, scheduler, logger;

protected:
	void processAMessage(EMessage* pMessage) {}
};

#endif