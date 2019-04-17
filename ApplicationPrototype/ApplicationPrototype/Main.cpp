// 
// 
// 

#include "Main.h"
#include "MemoryManager.h"

extern MemoryManager* pMMofMessage;

Main::Main() {
	pMMofMessage = new MemoryManager(sizeof(Message));
	this->pScheduler_ = new Scheduler();
}

Main::~Main() {
	delete this->pScheduler_;
	delete pMMofMessage;
}

void Main::initialize() {
	this->pScheduler_->initialize();
}

void Main::finalize() {
	this->pScheduler_->finalize();
	pMMofMessage->cleanUp();
}

void Main::run() {
	this->pScheduler_->run();
}

void Main::generateMessages() {}

void Main::processAMessage(Message* pMessage) {}