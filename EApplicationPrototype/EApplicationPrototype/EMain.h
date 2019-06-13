// EMain.h

#ifndef _EMAIN_h
#define _EMAIN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "EGlobal.h"
#include "EScheduler.h"
#include "ELifeCycleManager.h"

class EMain : public EComponent
{
private:
	// Attributes

	// Parts(components)
	EPLifeCycleManager lifeCycleManager;

	// Associations

public:
	EMain() : lifeCycleManager(this) {
	// 1. initialize attributes
	// 2. create components
	}
	~EMain() {}

// As a component: COMMON ////////////////////////
	void initialize() {
	// 3. associate components(sometimes, MUST be in constructor)
	// 4. initialize associated attributes

	// 5. initialize components(for child, chaning), 2 path initialization
	//           for( element : array )
	//                 initialize()
 	}
	void finalize() {}
	void generateAMessage() {}
	void processAMessage(EMessage* pMessage) {}
//////////////////////////////////////////////////

// As a system component: SPECIALIZED  ///////////////
	void initializeAsMain() {
		ELOG(ELOG_DEBUG, "EMain::initializeAsMain()", "");
		this->lifeCycleManager.initializeAsLifeCycleManager();
	}

	void runAsMain() {
		ELOG(ELOG_DEBUG, "EMain::runAsMain()", "");
		this->lifeCycleManager.run();
	}
///////////////////////////////////////////////////////
};

#endif