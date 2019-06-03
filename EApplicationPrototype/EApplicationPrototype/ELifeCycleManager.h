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
		ELOG(ELOG_INFO, "ELifeCycleManager::run()", "");
		this->scheduler.run();
	}
};

// User programming area	///////////////////////////////////
class EPLifeCycleManager : public ELifeCycleManager
{
protected:
	ETimer timer;
	EDummySender sender;
	EDummyReceiver receiver;

public:
	EPLifeCycleManager(EComponent* pMain) : ELifeCycleManager(pMain) {}
	~EPLifeCycleManager() {}

	void createUserComponents() {}
	void registerUserComponents() {
		this->registerAComponent(&(this->timer));
		this->registerAComponent(&(this->sender));
		this->registerAComponent(&(this->receiver));
	}
	void associateSendersNReceivers() {
		this->associateASenderNAReceiver(&(this->sender), &(this->receiver));
	}
	void associateSourcesNTargets() {
		this->associateASourcesNATarget(&(this->timer), &(this->sender));
	}
};

#endif