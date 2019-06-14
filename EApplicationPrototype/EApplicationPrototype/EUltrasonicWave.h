// EUltrasonicWave.h

#ifndef _EULTRASONICWAVE_h
#define _EULTRASONICWAVE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "EChannel.h"

class EUltrasonicWave
{
public:
	enum EState {
		eReady,
		eRunning,
		eWaitForDeviceReady,
		eMeasuringReady,
		eWaitForMeasuring,
		eMeasuring,
		eNumStates
	};
	enum EChannelId {
		eIdTransmitter,
		eIdReceiver,
		eNumChannelIds
	};
private:
	EState eState;
	EChannel *pChannels[eNumChannelIds];
	unsigned long initialTime;
	unsigned long startTime;
public:
	EUltrasonicWave(EChannelId eIdTransmitter, EChannel *pChannelTransmitter, EChannelId eIdReceiver, EChannel *pChannelReceiver) {
		this->pChannels[eIdTransmitter] = pChannelTransmitter;
		this->pChannels[eIdReceiver] = pChannelReceiver;
	}
	~EUltrasonicWave() {}
	void initialize() {
		this->initialTime = micros();
		this->eState = EState::eReady;
	}
	void finalize() {}
	int read() {
		if (this->eState == EState::eReady) {
			this->initialTime = micros();
			this->pChannels[eIdTransmitter]->write(HIGH);
			this->startTime = micros();
			this->eState = EState::eWaitForDeviceReady;
		}
		else if (this->eState == EState::eWaitForDeviceReady) {
			if (micros() - this->startTime > 10){
				this->pChannels[eIdTransmitter]->write(LOW);
				this->eState = EState::eMeasuringReady;
			}
		}
		else if (this->eState == EState::eMeasuringReady) {
			if (this->pChannels[eIdReceiver]->read() == LOW) {
				this->eState = EState::eWaitForMeasuring;
			}
		}
		else if (this->eState == EState::eWaitForMeasuring) {
			if (this->pChannels[eIdReceiver]->read() == HIGH) {
				this->startTime = micros();
				this->eState = EState::eMeasuring;
			}
		}
		else if (this->eState == EState::eMeasuring) {
			if (this->pChannels[eIdReceiver]->read() == LOW) {
				this->eState = EState::eReady;
				return micros() - this->startTime;
			}
		}
		if (micros() - this->initialTime > MJUC_TIME_OUT_OF_MEASURING_IN_MICROSECOND) {
			this->eState = EState::eReady;
		}
		return 0;
	}
};

#endif

