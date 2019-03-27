// UltrasonicWaveReceiver.h

#ifndef _ULTRASONICWAVERECEIVER_h
#define _ULTRASONICWAVERECEIVER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Sensor.h"
#include "Channel.h"

class UltrasonicWaveReceiver : public Sensor
{
public:
	enum EState {
		eReady,
		eRunning,
		ePrevHigh,
		eLow,
		eHigh,
		eNumStates
	};
	enum EChannelId {
		eIdReceive,
		eNumChannelIds
	};
private:
	EState eState;
	Channel *pChannels[eNumChannelIds];
	int readValue_;
	unsigned long initialTime_;
	unsigned long startTime_;
	unsigned long elapsedTime_;

public:
	UltrasonicWaveReceiver(EChannelId eIdReceive, Channel *pProximityChannelReceive) {
		this->pChannels[eIdReceive] = pProximityChannelReceive;
	}

	~UltrasonicWaveReceiver() {}

	void initialize() {
		for (Channel *pChannel : this->pChannels) {
			pChannel->initialize();
		}
		this->eState = EState::eReady;
	}
	void finalize() {
		for (Channel *pChannel : this->pChannels) {
			pChannel->finalize();
		}
	}

	unsigned long getElapsedTime() {
		return this->elapsedTime_;
	}

	void start() {
		if (this->eState == EState::eReady) {
			this->eState = EState::eRunning;
			this->initialTime_ = micros();
		}
	}

	bool wait() {
		if (micros() - this->initialTime_ > 1000000000) {
			this->elapsedTime_ = 0;
//			Serial.println("Time out");
			return true;
		}

		if (this->eState == EState::eRunning) {
			this->pChannels[eIdReceive]->read();
			this->readValue_ = this->pChannels[eIdReceive]->getData();
			
//			Serial.print("eRunning->");
			if (this->readValue_ == HIGH) {
				this->eState = EState::ePrevHigh;
//				Serial.println("ePrevHigh");
			}
			else {
				this->eState = EState::eLow;
//				Serial.println("eLow(Start)");
			}
			return false;
		}
		else if (this->eState == EState::ePrevHigh) {
			this->pChannels[eIdReceive]->read();
			this->readValue_ = this->pChannels[eIdReceive]->getData();

//			Serial.print("ePrevHigh->");
			if (this->readValue_ == LOW) {
				this->eState = EState::eLow;
//				Serial.println("eLow");
				return false;
			}
			return false;
		}
		else if (this->eState == EState::eLow) {
			this->pChannels[eIdReceive]->read();
			this->readValue_ = this->pChannels[eIdReceive]->getData();

//			Serial.print("eLow->");
			if (this->readValue_ == HIGH) {
				this->startTime_ = micros();
				this->eState = EState::eHigh;
//				Serial.println("eHigh");
				return false;
			}
			return false;
		}
		else if (this->eState == EState::eHigh) {
			this->pChannels[eIdReceive]->read();
			this->readValue_ = this->pChannels[eIdReceive]->getData();

//			Serial.print("eHigh->");
			if (this->readValue_ == LOW) {
				this->elapsedTime_ = micros() - this->startTime_;
				this->eState = EState::eReady;
//				Serial.println("eReady");
				return true;
			}
			return false;
		}
		return false;
	}
};

#endif

