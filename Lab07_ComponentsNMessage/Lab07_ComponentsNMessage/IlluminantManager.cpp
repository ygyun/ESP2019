// 
// 
// 

#include "IlluminantManager.h"

extern MessageQueue* pMessageQueue;

IlluminantManager::IlluminantManager(Component* pTargetComponent):
	illuminantChannel_(MJUC_CHANNEL_ILLUMINANT),
	illuminant_(Illuminant::EChannelId::eIdCDS, &illuminantChannel_),
	pTargetComponent_(pTargetComponent) {}

IlluminantManager::~IlluminantManager() {}

void IlluminantManager::initialize() {
	this->illuminant_.initialize();
	this->eState_ = EState::eReady;
}

void IlluminantManager::finalize() {
	this->illuminant_.finalize();
}

void IlluminantManager::generateMessage() {
	this->illuminant_.sense();

	int* pValue = new int;
	*pValue = this->illuminant_.getState();

	Message* msg = new Message(Message::EMessageType::eNumMessageTypes, this->pTargetComponent_, this, (void *)pValue);
	pMessageQueue->put(msg);
}

void IlluminantManager::processMessage(Message* pMessage) {
}

