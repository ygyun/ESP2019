// EIlluminant.h

#ifndef _EILLUMINANT_h
#define _EILLUMINANT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "EComponent.h"
#include "EAnalogInputChannel.h"
#include "EPhotoResistor.h"
#include "ETimer.h"
#include "ELightEmittingDiode.h"

class EIlluminant: public EComponent
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
	EAnalogInputChannel photoResistorChannel;
	EPhotoResistor photoResistor;
public:
	EIlluminant():
		photoResistorChannel(MJUC_CHANNEL_ILLUMINANT),
		photoResistor(EPhotoResistor::EChannelId::eIdCDS, &photoResistorChannel)	{}
	~EIlluminant() {}
	void initialize() {
		photoResistorChannel.initialize();
		photoResistor.initialize();
		this->eState = EState::eReady;
	}
	void finalize() {
		photoResistorChannel.finalize();
		photoResistor.finalize();
	}
	void generateAMessage() {
		if (this->eState == EState::eRunning) {
			int cds = photoResistor.read();
			ELOG(ELOG_INFO, "Photo Resister read(): ", cds);
			ELightEmittingDiode::ELightState lightState = cds > MJUC_LIGHT_DISTINCTION ?
				ELightEmittingDiode::ELightState::eBright : ELightEmittingDiode::ELightState::eDark;

			for (EComponent *pComponent : this->pReceivers) {
				ELOG(ELOG_DEBUG, "EIlluminant is GENerating a msg.", "");
				pComponent->addAReceiverMessage(ELightEmittingDiode::EMessageType::eLightState, pComponent, lightState);
			}
			this->eState = EState::eReady;
		}
	}
	void processAMessage(EMessage* pMessage) {
		ELOG(ELOG_DEBUG, "EIlluminant is PROcessing a msg.", "");
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

