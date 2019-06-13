// ELightEmittingDiode.h

#ifndef _ELIGHTEMITTINGDIODE_h
#define _ELIGHTEMITTINGDIODE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "EComponent.h"
#include "EPWMOutputChannel.h"
#include "ERGBLED.h"

class ELightEmittingDiode: public EComponent
{
public:
	enum EMessageType {
		eLightState,
		eDistanceState,
		eNumMessageTypes
	};
	enum EState {
		eReady,
		eRunning,
		eNumStates
	};
	enum ELightState {
		eBright,
		eDark,
		eNumLightStates
	};
	enum EDistanceState {
		eTooClose,
		eVeryClose,
		eClose,
		eFar,
		eVeryFar,
		eUnknown,
		eNumDistanceStates
	};
	typedef struct _RBGValue {
		int _R;
		int _G;
		int _B;
	} RGBValue;
private:
	EState eState;
	EPWMOutputChannel rgbLEDchannelRed;
	EPWMOutputChannel rgbLEDchannelGreen;
	EPWMOutputChannel rgbLEDchannelBlue;
	ERGBLED rgbLED;
	RGBValue rgbValues[ELightState::eNumLightStates][EDistanceState::eNumDistanceStates];
	unsigned int indexLightState;
	unsigned int indexDistanceState;
public:
	ELightEmittingDiode():
		rgbLEDchannelRed(MJUC_CHANNEL_RGBLED_RED),
		rgbLEDchannelGreen(MJUC_CHANNEL_RGBLED_GREEN),
		rgbLEDchannelBlue(MJUC_CHANNEL_RGBLED_BLUE),
		rgbLED(
			ERGBLED::EChannelId::eIdRed, &rgbLEDchannelRed,
			ERGBLED::EChannelId::eIdGreen, &rgbLEDchannelGreen,
			ERGBLED::EChannelId::eIdBlue, &rgbLEDchannelBlue)
	{
		rgbValues[ELightState::eBright][EDistanceState::eTooClose]._R = 0;
		rgbValues[ELightState::eBright][EDistanceState::eTooClose]._G = 0;
		rgbValues[ELightState::eBright][EDistanceState::eTooClose]._B = 0;
		rgbValues[ELightState::eBright][EDistanceState::eVeryClose]._R = MJUC_LED_STRENGTH_STRONG;
		rgbValues[ELightState::eBright][EDistanceState::eVeryClose]._G = 0;
		rgbValues[ELightState::eBright][EDistanceState::eVeryClose]._B = 0;
		rgbValues[ELightState::eBright][EDistanceState::eClose]._R = MJUC_LED_STRENGTH_STRONG;
		rgbValues[ELightState::eBright][EDistanceState::eClose]._G = MJUC_LED_STRENGTH_STRONG;
		rgbValues[ELightState::eBright][EDistanceState::eClose]._B = 0;
		rgbValues[ELightState::eBright][EDistanceState::eFar]._R = 0;
		rgbValues[ELightState::eBright][EDistanceState::eFar]._G = MJUC_LED_STRENGTH_STRONG;
		rgbValues[ELightState::eBright][EDistanceState::eFar]._B = 0;
		rgbValues[ELightState::eBright][EDistanceState::eVeryFar]._R = 0;
		rgbValues[ELightState::eBright][EDistanceState::eVeryFar]._G = 0;
		rgbValues[ELightState::eBright][EDistanceState::eVeryFar]._B = MJUC_LED_STRENGTH_STRONG;
		rgbValues[ELightState::eBright][EDistanceState::eUnknown]._R = 0;
		rgbValues[ELightState::eBright][EDistanceState::eUnknown]._G = 0;
		rgbValues[ELightState::eBright][EDistanceState::eUnknown]._B = 0;

		rgbValues[ELightState::eDark][EDistanceState::eTooClose]._R = 0;
		rgbValues[ELightState::eDark][EDistanceState::eTooClose]._G = 0;
		rgbValues[ELightState::eDark][EDistanceState::eTooClose]._B = 0;
		rgbValues[ELightState::eDark][EDistanceState::eVeryClose]._R = MJUC_LED_STRENGTH_WEAK;
		rgbValues[ELightState::eDark][EDistanceState::eVeryClose]._G = 0;
		rgbValues[ELightState::eDark][EDistanceState::eVeryClose]._B = 0;
		rgbValues[ELightState::eDark][EDistanceState::eClose]._R = MJUC_LED_STRENGTH_WEAK;
		rgbValues[ELightState::eDark][EDistanceState::eClose]._G = MJUC_LED_STRENGTH_WEAK;
		rgbValues[ELightState::eDark][EDistanceState::eClose]._B = 0;
		rgbValues[ELightState::eDark][EDistanceState::eFar]._R = 0;
		rgbValues[ELightState::eDark][EDistanceState::eFar]._G = MJUC_LED_STRENGTH_WEAK;
		rgbValues[ELightState::eDark][EDistanceState::eFar]._B = 0;
		rgbValues[ELightState::eDark][EDistanceState::eVeryFar]._R = 0;
		rgbValues[ELightState::eDark][EDistanceState::eVeryFar]._G = 0;
		rgbValues[ELightState::eDark][EDistanceState::eVeryFar]._B = MJUC_LED_STRENGTH_WEAK;
		rgbValues[ELightState::eDark][EDistanceState::eUnknown]._R = 0;
		rgbValues[ELightState::eDark][EDistanceState::eUnknown]._G = 0;
		rgbValues[ELightState::eDark][EDistanceState::eUnknown]._B = 0;
	}
	~ELightEmittingDiode() {}
	void initialize() {
		rgbLEDchannelRed.initialize();
		rgbLEDchannelGreen.initialize();
		rgbLEDchannelBlue.initialize();
		rgbLED.initialize();

		indexLightState = 0;
		indexDistanceState = 0;
	}
	void finalize() {
		rgbLEDchannelRed.finalize();
		rgbLEDchannelGreen.finalize();
		rgbLEDchannelBlue.finalize();
		rgbLED.finalize();
	}
	void generateAMessage() {}
	void processAMessage(EMessage* pMessage) {
		ELOG(ELOG_DEBUG, "ELightEmittingDiode is PROcessing a msg.", "");
		if (pMessage->getType() == EMessageType::eLightState) {
			this->indexLightState = pMessage->getIArg();
		}
		else if (pMessage->getType() == EMessageType::eDistanceState) {
			this->indexDistanceState = pMessage->getIArg();
		}
		rgbLED.write(
			this->rgbValues[this->indexLightState][this->indexDistanceState]._R,
			this->rgbValues[this->indexLightState][this->indexDistanceState]._G,
			this->rgbValues[this->indexLightState][this->indexDistanceState]._B);
	}
};

#endif

