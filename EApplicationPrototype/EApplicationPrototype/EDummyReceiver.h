// EDummyReceiver.h

#ifndef _EDUMMYRECEIVER_h
#define _EDUMMYRECEIVER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "EComponent.h"

class EDummyReceiver: public EComponent
{
protected:
	void processAMessage(EMessage* pMessage) {}
};

#endif

