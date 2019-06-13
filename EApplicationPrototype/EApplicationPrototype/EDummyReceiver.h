// EDummyReceiver.h

#ifndef _EDUMMYRECEIVER_h
#define _EDUMMYRECEIVER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "EComponent.h"

class EDummyReceiver : public EComponent
{
public:
	enum EMessageType {
		eNormal,
		eNumMessageTypes
	};
public:
	EDummyReceiver() {}
	~EDummyReceiver() {}
	void initialize() {}
	void finalize() {}
	void generateAMessage() {}
	void processAMessage(EMessage* pMessage) {
		ELOG(ELOG_DEBUG, "EDummyReceiver is PROcessing a msg.", "");
	}
};

#endif
