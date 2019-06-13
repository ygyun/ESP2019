// EDistance.h

#ifndef _EDISTANCE_h
#define _EDISTANCE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "EComponent.h"
#include "EDigitalInputChannel.h"
#include "EDigitalOutputChannel.h"
#include "EUltrasonicWave.h"
#include "ETimer.h"
#include "ELightEmittingDiode.h"

class EDistance: public EComponent
{
public:
	enum EState {
		eReady,
		eRunning,
		eStopped,
		eNumStates
	};
private:
	EState eState;
	EDigitalOutputChannel ultrasonicWaveChannelTransmitter;
	EDigitalInputChannel ultrasonicWaveChannelReceiver;
	EUltrasonicWave ultrasonicWave;
public:
	EDistance() :
		ultrasonicWaveChannelTransmitter(MJUC_CHANNEL_ULTRASONIC_WAVE_TRANSMITTER),
		ultrasonicWaveChannelReceiver(MJUC_CHANNEL_ULTRASONIC_WAVE_RECEIVER),
		ultrasonicWave(
			EUltrasonicWave::EChannelId::eIdTransmitter, &ultrasonicWaveChannelTransmitter,
			EUltrasonicWave::EChannelId::eIdReceiver, &ultrasonicWaveChannelReceiver) {}
		~EDistance() {}
	void initialize() {
		ultrasonicWaveChannelTransmitter.initialize();
		ultrasonicWaveChannelReceiver.initialize();
		ultrasonicWave.initialize();
		this->eState = EState::eReady;
	}
	void finalize() {
		ultrasonicWaveChannelTransmitter.finalize();
		ultrasonicWaveChannelReceiver.finalize();
		ultrasonicWave.finalize();
	}
	void generateAMessage() {
		if (this->eState == EState::eRunning) {
			int distance = ultrasonicWave.read() / MJUC_DIVISOR_FOR_DISTANCE_CALCULATION;

			if (distance > 0) {
				ELOG(ELOG_INFO, "UltrasonicWave read() - distance(cm): ", distance);
				ELightEmittingDiode::EDistanceState distanceState;
				if (distance < MJUC_DISTANCE_TOO_CLOSE) {
					distanceState = ELightEmittingDiode::EDistanceState::eTooClose;
				}
				else if (distance < MJUC_DISTANCE_VERY_CLOSE) {
					distanceState = ELightEmittingDiode::EDistanceState::eVeryClose;
				}
				else if (distance < MJUC_DISTANCE_CLOSE) {
					distanceState = ELightEmittingDiode::EDistanceState::eClose;
				}
				else if (distance < MJUC_DISTANCE_FAR) {
					distanceState = ELightEmittingDiode::EDistanceState::eFar;
				}
				else if (distance < MJUC_DISTANCE_VERY_FAR) {
					distanceState = ELightEmittingDiode::EDistanceState::eVeryFar;
				}
				else {
					distanceState = ELightEmittingDiode::EDistanceState::eUnknown;
				}

				for (EComponent *pComponent : this->pReceivers) {
					ELOG(ELOG_DEBUG, "EDistance is GENerating a msg.", "");
					pComponent->addAReceiverMessage(ELightEmittingDiode::EMessageType::eDistanceState, pComponent, distanceState);
				}
				this->eState = EState::eReady;
			}
		}
	}
	void processAMessage(EMessage* pMessage) {
		ELOG(ELOG_DEBUG, "EDistance is PROcessing a msg.", "");
		switch (pMessage->getType())
		{
		case ETimer::EMessageType::eWakeUp:
			if (this->eState == EState::eReady) {
				this->eState = EState::eRunning;
			}
			break;
		default:
			break;
		}
	}
};


#endif

