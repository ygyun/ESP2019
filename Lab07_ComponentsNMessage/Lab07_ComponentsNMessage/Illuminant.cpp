// 
// 
// 

#include "Illuminant.h"

Illuminant::Illuminant(EChannelId eIdCDS, Channel *pIlluminatChannel) {
	this->pChannels_[eIdCDS] = pIlluminatChannel;
}

Illuminant::~Illuminant() {}

void Illuminant::initialize() {
	for (Channel *pChannel : this->pChannels_) {
		pChannel->initialize();
	}
}

void Illuminant::finalize() {
	for (Channel *pChannel : this->pChannels_) {
		pChannel->finalize();
	}
}

void Illuminant::sense() {
	this->cdsLight_ = this->pChannels_[eIdCDS]->read();
}

int Illuminant::getState() {
	return this->cdsLight_ > MJUC_LIGHT_DISTINCTION ? ELightState::eBright : ELightState::eDark;
}