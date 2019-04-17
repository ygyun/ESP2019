// 
// 
// 

#include "Proximity.h"

Proximity::Proximity() {
	this->pChannelUltrasonicWaveTransmitter_ = new DigitalOutputChannel(MJUC_CHANNEL_ULTRASONIC_WAVE_TRANSMITTER);
	this->pChannelUltrasonicWaveReceiver_ = new DigitalInputChannel(MJUC_CHANNEL_ULTRASONIC_WAVE_RECEIVER);
	this->pUltrasonicWave_ = new UltrasonicWave(UltrasonicWave::EChannelId::eIdTransmitter, pChannelUltrasonicWaveTransmitter_,
		UltrasonicWave::EChannelId::eIdReceiver, pChannelUltrasonicWaveReceiver_);
}

Proximity::~Proximity() {
	delete this->pChannelUltrasonicWaveTransmitter_;
	delete this->pChannelUltrasonicWaveReceiver_;
	delete this->pUltrasonicWave_;
}

void Proximity::initialize() {
	this->pUltrasonicWave_->initialize();
}

void Proximity::finalize() {
	this->pUltrasonicWave_->finalize();
}

void Proximity::generateMessages() {
	EDistanceState msgArgument;

	this->dDistance_ = this->pUltrasonicWave_->read() / MJUC_DIVISOR_FOR_DISTANCE_CALCULATION;
	if (this->dDistance_ <= 0) {
		return;
	}
	else if (this->dDistance_ < MJUC_DISTANCE_TOO_CLOSE) {
		msgArgument = EDistanceState::eTooClose;
	}
	else if (this->dDistance_ < MJUC_DISTANCE_VERY_CLOSE) {
		msgArgument = EDistanceState::eVeryClose;
	}
	else if (this->dDistance_ < MJUC_DISTANCE_CLOSE) {
		msgArgument = EDistanceState::eClose;
	}
	else if (this->dDistance_ < MJUC_DISTANCE_FAR) {
		msgArgument = EDistanceState::eFar;
	}
	else {
		msgArgument = EDistanceState::eVeryFar;
	}
	createAMessage(Component::EMessageType::eDistanceState, msgArgument);
}

void Proximity::processAMessage(Message* pMessage) {}