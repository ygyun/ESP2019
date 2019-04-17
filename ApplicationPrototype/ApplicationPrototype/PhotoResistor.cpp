// 
// 
// 

#include "PhotoResistor.h"

PhotoResistor::PhotoResistor(EChannelId eIdCDS, Channel *pChannelPhotoResistor) {
	this->pChannels_[eIdCDS] = pChannelPhotoResistor;
}

PhotoResistor::~PhotoResistor() {}

void PhotoResistor::initialize() {
	for (Channel *pChannel : this->pChannels_) {
		pChannel->initialize();
	}
}

void PhotoResistor::finalize() {
	for (Channel *pChannel : this->pChannels_) {
		pChannel->finalize();
	}
}

int PhotoResistor::read() {
	return this->pChannels_[eIdCDS]->read();
}