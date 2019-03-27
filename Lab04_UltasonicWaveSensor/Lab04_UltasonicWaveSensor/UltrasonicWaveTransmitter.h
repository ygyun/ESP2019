// UltrasonicWaveTransmitter.h

#ifndef _ULTRASONICWAVETRANSMITTER_h
#define _ULTRASONICWAVETRANSMITTER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Actuator.h"

class UltrasonicWaveTransmitter : public Actuator
{
public:
	enum EState {
		eReady,
		eRunning,
		eTransmitting,
		eNumStates
	};
	enum EChannelId {
		eIdTransmit,
		eNumChannelIds
	};
private:
	EState eState;
	Channel *pChannels[eNumChannelIds];
	unsigned long startTime_;
	unsigned long elapsedTime_;
public:
	UltrasonicWaveTransmitter(EChannelId eIdTransmit, Channel *pProximityChannelTransmit) {
		this->pChannels[eIdTransmit] = pProximityChannelTransmit;
	}

	~UltrasonicWaveTransmitter() {}

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

	void start() {
		if (this->eState == EState::eReady) {
			this->eState = EState::eRunning;
		}
	}

	bool wait() {
		if (this->eState == EState::eRunning) {
			this->pChannels[eIdTransmit]->setData(HIGH);
			this->pChannels[eIdTransmit]->write();
			this->startTime_ = micros();
			this->eState = EState::eTransmitting;
			return false;
		}
		else if (this->eState == EState::eTransmitting) {
			this->elapsedTime_ = micros() - this->startTime_;
			if (this->elapsedTime_ > 10) {
				this->pChannels[eIdTransmit]->setData(LOW);
				this->pChannels[eIdTransmit]->write();
				this->eState = EState::eReady;
				return true;
			}
			return false;
		}
		return false;
	}
};

#endif

