// 
// 
// 

#include "UltrasonicWave.h"

UltrasonicWave::UltrasonicWave(EChannelId eIdTransmitter, Channel *pChannelTransmitter,
	EChannelId eIdReceiver, Channel *pChannelReceiver) {
	this->pChannels_[eIdTransmitter] = pChannelTransmitter;
	this->pChannels_[eIdReceiver] = pChannelReceiver;
}

UltrasonicWave::~UltrasonicWave() {}

void UltrasonicWave::initialize() {
	for (Channel *pChannel : this->pChannels_) {
		pChannel->initialize();
	}
	this->eState_ = EState::eReady;
	this->initialTime_ = micros();
}

void UltrasonicWave::finalize() {
	for (Channel *pChannel : this->pChannels_) {
		pChannel->finalize();
	}
}

int UltrasonicWave::read() {
	if (micros() - this->initialTime_ > MJUC_TIME_OUT_OF_MEASURING_IN_MICROSECOND) {
		this->elapsedTime_ = 0;
		this->eState_ = EState::eReady;
		this->initialTime_ = micros();
		return 0;
	}

	if (this->eState_ == EState::eReady) {
		this->pChannels_[eIdTransmitter]->write(HIGH);
		this->startTime_ = micros();
		this->eState_ = EState::eWaitForDeviceReady;
	}
	else if (this->eState_ == EState::eWaitForDeviceReady) {
		if (micros() - this->startTime_ > 10) {
			this->pChannels_[eIdTransmitter]->write(LOW);
			this->eState_ = EState::eMeasuringReady;
		}
	}
	else if (this->eState_ == EState::eMeasuringReady) {
		if (this->pChannels_[eIdReceiver]->read() == LOW) {
			this->eState_ = EState::eWaitForMeasuring;
		}
	}
	else if (this->eState_ == EState::eWaitForMeasuring) {
		if (this->pChannels_[eIdReceiver]->read() == HIGH) {
			this->startTime_ = micros();
			this->eState_ = EState::eMeasuring;
		}
	}
	else if (this->eState_ == EState::eMeasuring) {
		if (this->pChannels_[eIdReceiver]->read() == LOW) {
			this->elapsedTime_ = micros() - this->startTime_;
			this->eState_ = EState::eReady;
			return this->elapsedTime_;
		}
	}
	return 0;
}