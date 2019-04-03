// 
// 
// 

#include "RGBLED.h"
#include "Globals.h"

RGBLED::RGBLED(EChannelId eIdRed, Channel *pChannelRed,
		       EChannelId eIdGreen, Channel *pChannelGreen,
			   EChannelId eIdBlue, Channel *pChannelBlue) {
	this->pChannels[eIdRed] = pChannelRed;
	this->pChannels[eIdGreen] = pChannelGreen;
	this->pChannels[eIdBlue] = pChannelBlue;

	rgbValues[ELightState::eBright][EDistanceState::eTooClose]._R = 0;
	rgbValues[ELightState::eBright][EDistanceState::eTooClose]._G = 0;
	rgbValues[ELightState::eBright][EDistanceState::eTooClose]._B = 0;
	rgbValues[ELightState::eBright][EDistanceState::eVeryClose]._R = MJUC_LED_STRENGTH_STRONG;
	rgbValues[ELightState::eBright][EDistanceState::eVeryClose]._G = 0;
	rgbValues[ELightState::eBright][EDistanceState::eVeryClose]._B = 0;
	rgbValues[ELightState::eBright][EDistanceState::eClose]._R = MJUC_LED_STRENGTH_STRONG;
	rgbValues[ELightState::eBright][EDistanceState::eClose]._G = MJUC_LED_STRENGTH_STRONG;
	rgbValues[ELightState::eBright][EDistanceState::eClose]._B = 0;
	rgbValues[ELightState::eBright][EDistanceState::eFar]._R = 0;
	rgbValues[ELightState::eBright][EDistanceState::eFar]._G = MJUC_LED_STRENGTH_STRONG;
	rgbValues[ELightState::eBright][EDistanceState::eFar]._B = 0;
	rgbValues[ELightState::eBright][EDistanceState::eVeryFar]._R = 0;
	rgbValues[ELightState::eBright][EDistanceState::eVeryFar]._G = 0;
	rgbValues[ELightState::eBright][EDistanceState::eVeryFar]._B = MJUC_LED_STRENGTH_STRONG;
	rgbValues[ELightState::eBright][EDistanceState::eUnknown]._R = 0;
	rgbValues[ELightState::eBright][EDistanceState::eUnknown]._G = 0;
	rgbValues[ELightState::eBright][EDistanceState::eUnknown]._B = 0;

	rgbValues[ELightState::eDark][EDistanceState::eTooClose]._R = 0;
	rgbValues[ELightState::eDark][EDistanceState::eTooClose]._G = 0;
	rgbValues[ELightState::eDark][EDistanceState::eTooClose]._B = 0;
	rgbValues[ELightState::eDark][EDistanceState::eVeryClose]._R = MJUC_LED_STRENGTH_WEAK;
	rgbValues[ELightState::eDark][EDistanceState::eVeryClose]._G = 0;
	rgbValues[ELightState::eDark][EDistanceState::eVeryClose]._B = 0;
	rgbValues[ELightState::eDark][EDistanceState::eClose]._R = MJUC_LED_STRENGTH_WEAK;
	rgbValues[ELightState::eDark][EDistanceState::eClose]._G = MJUC_LED_STRENGTH_WEAK;
	rgbValues[ELightState::eDark][EDistanceState::eClose]._B = 0;
	rgbValues[ELightState::eDark][EDistanceState::eFar]._R = 0;
	rgbValues[ELightState::eDark][EDistanceState::eFar]._G = MJUC_LED_STRENGTH_WEAK;
	rgbValues[ELightState::eDark][EDistanceState::eFar]._B = 0;
	rgbValues[ELightState::eDark][EDistanceState::eVeryFar]._R = 0;
	rgbValues[ELightState::eDark][EDistanceState::eVeryFar]._G = 0;
	rgbValues[ELightState::eDark][EDistanceState::eVeryFar]._B = MJUC_LED_STRENGTH_WEAK;
	rgbValues[ELightState::eDark][EDistanceState::eUnknown]._R = 0;
	rgbValues[ELightState::eDark][EDistanceState::eUnknown]._G = 0;
	rgbValues[ELightState::eDark][EDistanceState::eUnknown]._B = 0;
}

RGBLED::~RGBLED() {}

void RGBLED::initialize() {
	for (Channel *pChannel : this->pChannels) {
		pChannel->initialize();
	}
}
void RGBLED::finalize() {
	for (Channel *pChannel : this->pChannels) {
		pChannel->finalize();
	}
}

void RGBLED::actuate() {
	this->pChannels[eIdRed]->write(this->rgbValues[this->eLishtStateIndex_][this->eDistanceStateIndex_]._R);
	this->pChannels[eIdGreen]->write(this->rgbValues[this->eLishtStateIndex_][this->eDistanceStateIndex_]._G);
	this->pChannels[eIdBlue]->write(this->rgbValues[this->eLishtStateIndex_][this->eDistanceStateIndex_]._B);
}

void RGBLED::setState(int eLishtStateIndex, int eDistanceStateIndex) {
	this->eLishtStateIndex_ = eLishtStateIndex;
	this->eDistanceStateIndex_ = eDistanceStateIndex;
}

