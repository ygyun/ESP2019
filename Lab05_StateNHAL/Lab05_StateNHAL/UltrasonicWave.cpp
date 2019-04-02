// 
// 
// 

#include "UltrasonicWave.h"

UltrasonicWave::UltrasonicWave(EChannelId eIdTransmitter, Channel *pChannelTransmitter,
	EChannelId eIdReceiver, Channel *pChannelReceiver) {
	this->pChannels[eIdTransmitter] = pChannelTransmitter;
	this->pChannels[eIdReceiver] = pChannelReceiver;
}

UltrasonicWave::~UltrasonicWave() {}

void UltrasonicWave::initialize() {
	for (Channel *pChannel : this->pChannels) {
		pChannel->initialize();
	}
	this->eState = EState::eReady;
}

void UltrasonicWave::finalize() {
	for (Channel *pChannel : this->pChannels) {
		pChannel->finalize();
	}
}

void UltrasonicWave::start() {
	if (this->eState == EState::eReady) {
		this->initialTime_ = micros();
		this->eState = EState::eRunning;
	}
}

bool UltrasonicWave::wait() {
	if (micros() - this->initialTime_ > 1000000) {
		this->elapsedTime_ = 0;
		this->eState = EState::eReady;
		return true;
	}

	if (this->eState == EState::eRunning) {
		this->pChannels[eIdTransmitter]->write(HIGH);
		this->startTime_ = micros();
		this->eState = EState::eWaitForDeviceReady;
		return false;
	}
	else if (this->eState == EState::eWaitForDeviceReady) {
		if (micros() - this->startTime_ > 10) {
			this->pChannels[eIdTransmitter]->write(LOW);
			this->eState = EState::eMeasuringReady;
		}
		return false;
	}
	else if (this->eState == EState::eMeasuringReady) {
		if (this->pChannels[eIdReceiver]->read() == LOW) {
			this->eState = EState::eWaitForMeasuring;
		}
		return false;
	}
	else if (this->eState == EState::eWaitForMeasuring) {
		if (this->pChannels[eIdReceiver]->read() == HIGH) {
			this->startTime_ = micros();
			this->eState = EState::eMeasuring;
		}
		return false;
	}
	else if (this->eState == EState::eMeasuring) {
		if (this->pChannels[eIdReceiver]->read() == LOW) {
			this->elapsedTime_ = micros() - this->startTime_;
			this->eState = EState::eReady;
			return true;
		}
		return false;
	}
	return false;
}

unsigned long UltrasonicWave::getElapsedTime() {
	return this->elapsedTime_;
}