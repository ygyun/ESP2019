// 
// 
// 

#include "Illuminant.h"

Illuminant::Illuminant(EChannelId eIdCDS, Channel *pIlluminatChannel) {
	this->pChannels[eIdCDS] = pIlluminatChannel;
}

Illuminant::~Illuminant() {}

void Illuminant::initialize() {
	for (Channel *pChannel : this->pChannels) {
		pChannel->initialize();
	}
	this->eState = EState::eReady;
}

void Illuminant::finalize() {
	for (Channel *pChannel : this->pChannels) {
		pChannel->finalize();
	}
}

void Illuminant::start() {
	if (this->eState == EState::eReady) {
		this->eState = EState::eRunning;
	}
}

bool Illuminant::wait() {
	if (this->eState == EState::eRunning) {
		for (Channel *pChannel : this->pChannels) {
			this->cdsLight_ = pChannel->read();
		}
		this->eState = EState::eReady;
		return true;
	}
	return false;
}

int Illuminant::getCDSLight() {
	return this->cdsLight_;
}
