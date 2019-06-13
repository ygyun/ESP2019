// ELifeCycleManager.h

#ifndef _ELIFECYCLEMANAGER_h
#define _ELIFECYCLEMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "EGlobal.h"
#include "EComponent.h"
#include "ETimer.h"
#include "EDummySender.h"
#include "EDummyReceiver.h"
#include "EIlluminant.h"
#include "EDistance.h"
#include "ELightEmittingDiode.h"

class ELifeCycleManager : public EComponent
{
private:
	EArray<EComponent*> pComponents;
		EComponent* pMain;
		EScheduler scheduler;	// to be chanded to * and a main
//		ELogManager logManager;
//		EExceptionManager exceptionManager;

protected:
	void createComponents() {
		this->createSystemComponents();
		this->createUserComponents();
	}
	void createSystemComponents() {}

	void registerComponents() {
		this->registerSystemComponents();
		this->registerUserComponents();
	}
	void registerSystemComponents() {
		this->registerAComponent(this->pMain);
		this->registerAComponent(this);
		this->registerAComponent(&(this->scheduler));
//		this->registerAComponent(&logManager_);
	}
	void registerAComponent(EComponent* pComponent) {
		this->pComponents.add(pComponent);
		pComponent->setPMessageQueue(&(scheduler.getMessageQueue()));
	}

	void associateASenderNAReceiver(EComponent* pSender, EComponent* pReceiver) {
		pSender->associateAReceiver(pReceiver);
		this->scheduler.addAMessageGeneratingComponent(pSender);
	}

	void associateASourcesNATarget(EComponent* pSource, EComponent* pTarget) {
		pSource->associateATarget(pTarget);
		this->scheduler.addAMessageGeneratingComponent(pSource);
	}

	virtual void createUserComponents() = 0;
	virtual void registerUserComponents() = 0;
	virtual void associateSendersNReceivers() = 0;
	virtual void associateSourcesNTargets() = 0;

public:
	ELifeCycleManager(EComponent* pMain) : pMain(pMain) {}
	virtual ~ELifeCycleManager() {}
	void initialize() {}
	void finalize() {}
	void generateAMessage() {}
	void processAMessage(EMessage* pMessage) {}

	// initialize As Component
	// initialize As LifeCycleManager
	// initialize As Task
	void initializeAsLifeCycleManager() {
		// As a boot up   /////////////////////////////
		this->createComponents();
		this->registerComponents();
		this->associateSendersNReceivers();
		this->associateSourcesNTargets();
		///////////////////////////////////////////////

		// if needed, might be PAUSED here

		// As a system, initialize components /////////
		for (EComponent* pComponent : pComponents) {
			ELOG(ELOG_DEBUG, "ELifeCycleManager: Initialize a Component", "");
			pComponent->initialize();
		}
		///////////////////////////////////////////////
	}

	void run() {
		ELOG(ELOG_DEBUG, "ELifeCycleManager::run()", "");
		this->scheduler.run();
	}
};

// User programming area	///////////////////////////////////
class EPLifeCycleManager : public ELifeCycleManager
{
protected:
	ETimer timerIlluminant;
	ETimer timerDistance;
//	EDummySender sender;
//	EDummyReceiver receiver;
	EIlluminant illuminant;
	EDistance distance;
	ELightEmittingDiode lightEmittingDiode;

public:
	EPLifeCycleManager(EComponent* pMain):
		ELifeCycleManager(pMain),
		timerIlluminant(TIMER_TIMEOUT_ILLUMINANT),
		timerDistance(TIMER_TIMEOUT_DISTANCE)	{}
	~EPLifeCycleManager() {}

	void createUserComponents() {}
	void registerUserComponents() {
		this->registerAComponent(&(this->timerIlluminant));
		this->registerAComponent(&(this->timerDistance));
		this->registerAComponent(&(this->illuminant));
		this->registerAComponent(&(this->distance));
		this->registerAComponent(&(this->lightEmittingDiode));
	}
	void associateSendersNReceivers() {
		this->associateASenderNAReceiver(&(this->illuminant), &(this->lightEmittingDiode));
		this->associateASenderNAReceiver(&(this->distance), &(this->lightEmittingDiode));
	}
	void associateSourcesNTargets() {
		this->associateASourcesNATarget(&(this->timerIlluminant), &(this->illuminant));
		this->associateASourcesNATarget(&(this->timerDistance), &(this->distance));
	}
};

#endif