// 
// 
// 

#include "RGBLED.h"

RGBLED::RGBLED(EChannelId eIdRed, Channel *pChannelRed,
		       EChannelId eIdGreen, Channel *pChannelGreen,
			   EChannelId eIdBlue, Channel *pChannelBlue) {
	this->pChannels[eIdRed] = pChannelRed;
	this->pChannels[eIdGreen] = pChannelGreen;
	this->pChannels[eIdBlue] = pChannelBlue;
}

RGBLED::~RGBLED() {}

void RGBLED::initialize() {
	for (Channel *pChannel : this->pChannels) {
		pChannel->initialize();
	}
	this->eState = EState::eReady;
}
void RGBLED::finalize() {
	for (Channel *pChannel : this->pChannels) {
		pChannel->finalize();
	}
}

void RGBLED::start() {
	if (this->eState == EState::eReady) {
		this->eState = EState::eRunning;
	}
}

bool RGBLED::wait() {
	if (this->eState == EState::eRunning) {
		this->pChannels[eIdRed]->write(this->rgbValue._R);
		this->pChannels[eIdGreen]->write(this->rgbValue._G);
		this->pChannels[eIdBlue]->write(this->rgbValue._B);
		this->eState = EState::eReady;
		return true;
	}
	return false;
}

void RGBLED::setRGBValue(int R, int G, int B) {
	this->rgbValue._R = R;
	this->rgbValue._G = G;
	this->rgbValue._B = B;
}