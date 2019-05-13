// ELifeCycleManager.h

#ifndef _ELIFECYCLEMANAGER_h
#define _ELIFECYCLEMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "EComponent.h"
#include "ETimer.h"
#include "EDummySender.h"
#include "EDummyReceiver.h"

class ELifeCycleManager: public EComponent
{
private:
	EComponent* pComponents[10];
	unsigned int index = 0;
protected:
	EScheduler scheduler;
//	ELogManager logManager;

	void createComponents() {
		this->createSystemComponents();
		this->createUserComponents();
	}
	void createSystemComponents() {
		// to do
	}
	void registerComponents() {
		this->registerSystemComponents();
		this->registerUserComponents();
	}
	void registerAComponent(EComponent* pComponent) {
		this->pComponents[index++] = pComponent;
	}
	void registerSystemComponents() {
		this->registerAComponent(&main);
		this->registerAComponent(&scheduler);
//		this->registerAComponent(&logManager);
		this->registerAComponent(this);
	}
	void associateASenderNAReceiver(EComponent* pSender, EComponent* pReceiver) {}
	void associateASourcesNATarget(EComponent* pSource, EComponent* pTarget) {}

	virtual void createUserComponents() = 0;
	virtual void registerUserComponents() = 0;
	virtual void associateSendersNReceivers() = 0;
	virtual void associateSourcesNTargets() = 0;
	virtual void processAMessage(EMessage* pMessage) = 0;

public:
	ELifeCycleManager() {}
	virtual ~ELifeCycleManager() {}
	void initialize() {
		this->createComponents();
		this->registerComponents();
		this->associateSendersNReceivers();
		this->associateSourcesNTargets();
	
		this->scheduler.initialize();
	}
	void finalize() {
		this->scheduler.finalize();
	}
	void run() {
		this->scheduler.run();
	}
};

class PELifeCycleManager : public ELifeCycleManager {
public:
	ETimer timer;

	EDummySender sender;
	EDummyReceiver receiver;

	void createUserComponents() {}
	void registerUserComponents() {
		this->registerAComponent(&timer);
		this->registerAComponent(&sender);
		this->registerAComponent(&receiver);
	}
	void associateSendersNReceivers() {
		associateASenderNAReceiver(&sender, &receiver);
	}
	void associateSourcesNTargets() {
		this->associateASourcesNATarget(&timer, &sender);
//		this->associateASourcesNATarget(&sender, &receiver);
	}
	void processAMessage(EMessage* pMessage) {}
};

#endif

