// 
// 
// 

#include "Scheduler.h"

Scheduler::Scheduler() {
	pIlluminant  = new Illuminant();
	pProximity = new Proximity();
	pLED = new LED();
	pLEDManagerWithLIghtNDistance = new LEDManagerWithLIghtNDistance();

	pIlluminant->associateWithATargetComponent(pLED);
	pProximity->associateWithATargetComponent(pLED);

	pSensorComponents_[0] = pIlluminant;
	pSensorComponents_[1] = pProximity;
	pActuatorComponents_[0] = pLED;
}

Scheduler::~Scheduler() {
	delete pIlluminant;
	delete pProximity;
	delete pLED;
	delete pLEDManagerWithLIghtNDistance;
}

void Scheduler::initialize() {
	for (Component* pComponent: this->pSensorComponents_) {
		pComponent->initialize();
	}
	for (Component* pComponent: this->pActuatorComponents_) {
		pComponent->initialize();
	}
	pLEDManagerWithLIghtNDistance->initialize();
}

void Scheduler::finalize() {
	for (Component* pComponent: this->pSensorComponents_) {
		pComponent->finalize();
	}
	for (Component* pComponent: this->pActuatorComponents_) {
		pComponent->finalize();
	}
	pLEDManagerWithLIghtNDistance->finalize();
}

void Scheduler::run() {
	Message* pMsg;
	Component* pComponent;

	while (true) {
		for (Component* pComponent : this->pSensorComponents_) {
			pComponent->generateMessages();
		}

		for (Component* pComponent : this->pSensorComponents_) {
			pMsg = pComponent->pMessageQueue_->get();
			while (pMsg != NULL) {
				this->pMessageQueue_->put(pMsg);
				pMsg = pComponent->pMessageQueue_->get();
			}
		}

		pMsg = this->pMessageQueue_->get();
		if (pMsg != NULL) {
			pComponent = pMsg->pTargetComponent_;
			if (pComponent != NULL) {
				pComponent->processAMessage(pMsg);
			}
		}
	}
}

void Scheduler::generateMessages() {}

void Scheduler::processAMessage(Message* pMessage) {}

