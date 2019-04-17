// 
// 
// 

#include "RGBLED.h"

RGBLED::RGBLED(EChannelId eIdRed, Channel *pChannelRed,
	EChannelId eIdGreen, Channel *pChannelGreen,
	EChannelId eIdBlue, Channel *pChannelBlue) {
	this->pChannels_[eIdRed] = pChannelRed;
	this->pChannels_[eIdGreen] = pChannelGreen;
	this->pChannels_[eIdBlue] = pChannelBlue;
}

RGBLED::~RGBLED() {}

void RGBLED::initialize() {
	for (Channel *pChannel : this->pChannels_) {
		pChannel->initialize();
	}
}
void RGBLED::finalize() {
	for (Channel *pChannel : this->pChannels_) {
		pChannel->finalize();
	}
}

void RGBLED::write( int R, int G, int B ) {
	this->pChannels_[eIdRed]->write(R);
	this->pChannels_[eIdGreen]->write(G);
	this->pChannels_[eIdBlue]->write(B);
}