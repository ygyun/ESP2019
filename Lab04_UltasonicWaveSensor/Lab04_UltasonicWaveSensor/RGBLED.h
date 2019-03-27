// RGBLED.h

#ifndef _RGBLED_h
#define _RGBLED_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Actuator.h"

class RGBLED : public Actuator
{
public:
	enum EState {
		eReady,
		eRunning,
		eNumStates
	};
	enum EChannelId {
		eIdRed,
		eIdGreen,
		eIdBlue,
		eNumChannelIds
	};
private:
	EState eState;
	Channel *pChannels[eNumChannelIds];
public:
	RGBLED(EChannelId eIdRed, Channel *pChannelRed,
		EChannelId eIdGreen, Channel *pChannelGreen,
		EChannelId eldBlue, Channel *pChannelBlue) {
		this->pChannels[eIdRed] = pChannelRed;
		this->pChannels[eIdGreen] = pChannelGreen;
		this->pChannels[eldBlue] = pChannelBlue;
	}

	~RGBLED() {}

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
			for (Channel *pChannel : this->pChannels) {
				pChannel->write();
			}
			this->eState = EState::eReady;
			return true;
		}
		return false;
	}
};

#endif

