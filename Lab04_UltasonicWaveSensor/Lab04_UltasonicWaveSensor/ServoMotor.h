// ServoMotor.h

#ifndef _SERVOMOTOR_h
#define _SERVOMOTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Actuator.h"
#include "Channel.h"

class ServoMotor : public Actuator
{
public:
	enum EState {
		eReady,
		eRunning,
		eNumStates
	};
	enum EChannelId {
		eIdAttach,
		eNumChannelIds
	};
private:
	EState eState;
	Channel *pChannels[eNumChannelIds];
public:
	ServoMotor(EChannelId eIdAttach, Channel *pServoMotorChannel) {
		this->pChannels[eIdAttach] = pServoMotorChannel;
	}

	~ServoMotor() {}

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
			this->pChannels[eIdAttach]->write();
			this->eState = EState::eReady;
			return true;
		}
		return false;
	}
};

#endif

