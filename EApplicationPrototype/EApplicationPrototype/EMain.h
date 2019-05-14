// EMain.h

#ifndef _EMAIN_h
#define _EMAIN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "EScheduler.h"
#include "ELifeCycleManager.h"

class EMain: public EScheduler
{
private:
	PELifeCycleManager lifeCycleManager;
public:
	EMain() {}
	~EMain() {}

	void initialize() {
		lifeCycleManager.initialize();
	}

	void finalize() {
		lifeCycleManager.finalize();
	}

	void processAMessage(EMessage* pMessage) {}

	void run() {
		lifeCycleManager.run();
	}
};

#endif