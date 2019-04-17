// 
// 
// 

#include "Illuminant.h"

Illuminant::Illuminant() {
	this->pChannelPhotoResistor_ = new AnalogInputChannel(MJUC_CHANNEL_PHOTO_RESISTOR),
	this->pPhotoResistor_ = new PhotoResistor(PhotoResistor::EChannelId::eIdCDS, pChannelPhotoResistor_);
}

Illuminant::~Illuminant() {
	delete this->pChannelPhotoResistor_;
	delete this->pPhotoResistor_;
}

void Illuminant::initialize() {
	this->pPhotoResistor_->initialize();
}

void Illuminant::finalize() {
	this->pPhotoResistor_->finalize();
}

void Illuminant::generateMessages() {
	ELightState msgArgument;

	this->cdsLight_ = this->pPhotoResistor_->read();
	if (this->cdsLight_ > MJUC_LIGHT_DISTINCTION) {
		msgArgument = ELightState::eBright;
	}
	else {
		msgArgument = ELightState::eDark;
	}
	createAMessage(Component::EMessageType::eLightState, msgArgument);
}

void Illuminant::processAMessage(Message* pMessage) {}
