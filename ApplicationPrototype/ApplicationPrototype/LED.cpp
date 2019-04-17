// 
// 
// 

#include "LED.h"

LED::LED() {
	this->pChannelrgbLEDRed_ = new PWMOutputChannel(MJUC_CHANNEL_RGBLED_RED);
	this->pChannelrgbLEDGreen_ = new PWMOutputChannel(MJUC_CHANNEL_RGBLED_GREEN);
	this->pChannelrgbLEDBlue_ = new PWMOutputChannel(MJUC_CHANNEL_RGBLED_BLUE);
	this->pRGBbLED_ = new RGBLED(RGBLED::EChannelId::eIdRed, pChannelrgbLEDRed_,
		RGBLED::EChannelId::eIdGreen, pChannelrgbLEDGreen_,
		RGBLED::EChannelId::eIdBlue, pChannelrgbLEDBlue_);

	rgbValues[Illuminant::ELightState::eBright][Proximity::EDistanceState::eTooClose]._R = 0;
	rgbValues[Illuminant::ELightState::eBright][Proximity::EDistanceState::eTooClose]._G = 0;
	rgbValues[Illuminant::ELightState::eBright][Proximity::EDistanceState::eTooClose]._B = 0;
	rgbValues[Illuminant::ELightState::eBright][Proximity::EDistanceState::eVeryClose]._R = 255;
	rgbValues[Illuminant::ELightState::eBright][Proximity::EDistanceState::eVeryClose]._G = 0;
	rgbValues[Illuminant::ELightState::eBright][Proximity::EDistanceState::eVeryClose]._B = 0;
	rgbValues[Illuminant::ELightState::eBright][Proximity::EDistanceState::eClose]._R = 255;
	rgbValues[Illuminant::ELightState::eBright][Proximity::EDistanceState::eClose]._G = 255;
	rgbValues[Illuminant::ELightState::eBright][Proximity::EDistanceState::eClose]._B = 0;
	rgbValues[Illuminant::ELightState::eBright][Proximity::EDistanceState::eFar]._R = 0;
	rgbValues[Illuminant::ELightState::eBright][Proximity::EDistanceState::eFar]._G = 255;
	rgbValues[Illuminant::ELightState::eBright][Proximity::EDistanceState::eFar]._B = 0;
	rgbValues[Illuminant::ELightState::eBright][Proximity::EDistanceState::eVeryFar]._R = 0;
	rgbValues[Illuminant::ELightState::eBright][Proximity::EDistanceState::eVeryFar]._G = 0;
	rgbValues[Illuminant::ELightState::eBright][Proximity::EDistanceState::eVeryFar]._B = 255;
	rgbValues[Illuminant::ELightState::eBright][Proximity::EDistanceState::eUnknown]._R = 0;
	rgbValues[Illuminant::ELightState::eBright][Proximity::EDistanceState::eUnknown]._G = 0;
	rgbValues[Illuminant::ELightState::eBright][Proximity::EDistanceState::eUnknown]._B = 0;

	rgbValues[Illuminant::ELightState::eDark][Proximity::EDistanceState::eTooClose]._R = 0;
	rgbValues[Illuminant::ELightState::eDark][Proximity::EDistanceState::eTooClose]._G = 0;
	rgbValues[Illuminant::ELightState::eDark][Proximity::EDistanceState::eTooClose]._B = 0;
	rgbValues[Illuminant::ELightState::eDark][Proximity::EDistanceState::eVeryClose]._R = 100;
	rgbValues[Illuminant::ELightState::eDark][Proximity::EDistanceState::eVeryClose]._G = 0;
	rgbValues[Illuminant::ELightState::eDark][Proximity::EDistanceState::eVeryClose]._B = 0;
	rgbValues[Illuminant::ELightState::eDark][Proximity::EDistanceState::eClose]._R = 100;
	rgbValues[Illuminant::ELightState::eDark][Proximity::EDistanceState::eClose]._G = 100;
	rgbValues[Illuminant::ELightState::eDark][Proximity::EDistanceState::eClose]._B = 0;
	rgbValues[Illuminant::ELightState::eDark][Proximity::EDistanceState::eFar]._R = 0;
	rgbValues[Illuminant::ELightState::eDark][Proximity::EDistanceState::eFar]._G = 100;
	rgbValues[Illuminant::ELightState::eDark][Proximity::EDistanceState::eFar]._B = 0;
	rgbValues[Illuminant::ELightState::eDark][Proximity::EDistanceState::eVeryFar]._R = 0;
	rgbValues[Illuminant::ELightState::eDark][Proximity::EDistanceState::eVeryFar]._G = 0;
	rgbValues[Illuminant::ELightState::eDark][Proximity::EDistanceState::eVeryFar]._B = 100;
	rgbValues[Illuminant::ELightState::eDark][Proximity::EDistanceState::eUnknown]._R = 0;
	rgbValues[Illuminant::ELightState::eDark][Proximity::EDistanceState::eUnknown]._G = 0;
	rgbValues[Illuminant::ELightState::eDark][Proximity::EDistanceState::eUnknown]._B = 0;

	this->indexI_ = 0;
	this->indexJ_ = 0;
}

LED::~LED() {
	delete this->pChannelrgbLEDRed_;
	delete this->pChannelrgbLEDGreen_;
	delete this->pChannelrgbLEDBlue_;
}

void LED::initialize() {
	this->pRGBbLED_->initialize();
}

void LED::finalize() {
	this->pRGBbLED_->finalize();
}

void LED::generateMessages() {}

void LED::processAMessage(Message* pMessage) {
	if (pMessage->messageType_ == Component::eLightState) {
		indexI_ = pMessage->uArgument_.iValue;
	}
	else if (pMessage->messageType_ == Component::eDistanceState) {
		indexJ_ = pMessage->uArgument_.iValue;
	}
	this->pRGBbLED_->write(
		this->rgbValues[indexI_][indexJ_]._R,
		this->rgbValues[indexI_][indexJ_]._G,
		this->rgbValues[indexI_][indexJ_]._B);
}