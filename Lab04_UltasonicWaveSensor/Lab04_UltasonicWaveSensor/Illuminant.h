// Illuminant.h

#ifndef _ILLUMINANT_h
#define _ILLUMINANT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Sensor.h"

class Illuminant : public Sensor
{
public:
	enum EState {
		eReady,
		eRunning,
		eNumStates
	};
	enum EChannelId {
		eIdCDS,
		eNumChannelIds
	};
private:
	EState eState;
	Channel *pChannels[eNumChannelIds];
public:
	Illuminant(EChannelId eIdCDS, Channel *pIlluminatChannel) {
		this->pChannels[eIdCDS] = pIlluminatChannel;
	}

	~Illuminant() {}

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
				pChannel->read();
			}
			this->eState = EState::eReady;
			return true;
		}
		return false;
	}
};

#endif

