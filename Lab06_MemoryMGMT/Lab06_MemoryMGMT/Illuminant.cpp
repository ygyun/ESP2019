// 
// 
// 

#include "Illuminant.h"
#include "Globals.h"

Illuminant::Illuminant(EChannelId eIdCDS, Channel *pIlluminatChannel) {
	this->pChannels[eIdCDS] = pIlluminatChannel;
}

Illuminant::~Illuminant() {}

void Illuminant::initialize() {
	for (Channel *pChannel : this->pChannels) {
		pChannel->initialize();
	}
}

void Illuminant::finalize() {
	for (Channel *pChannel : this->pChannels) {
		pChannel->finalize();
	}
}

void Illuminant::sense() {
	this->cdsLight_ = this->pChannels[eIdCDS]->read();
}

int Illuminant::getState() {
	return this->cdsLight_ > MJUC_LIGHT_DISTINCTION ? ELightState::eBright : ELightState::eDark;
}
