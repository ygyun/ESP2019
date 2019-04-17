// Proximity.h

#ifndef _PROXIMITY_h
#define _PROXIMITY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Component.h"
#include "DigitalInputChannel.h"
#include "DigitalOutputChannel.h"
#include "UltrasonicWave.h"

class Proximity: public Component
{
public:
	enum EDistanceState {
		eTooClose,
		eVeryClose,
		eClose,
		eFar,
		eVeryFar,
		eUnknown,
		eNumDistanceStates
	};
protected:
	DigitalOutputChannel* pChannelUltrasonicWaveTransmitter_;
	DigitalInputChannel* pChannelUltrasonicWaveReceiver_;
	UltrasonicWave* pUltrasonicWave_;
	double dDistance_;

public:
	Proximity();
	~Proximity();
	void initialize();
	void finalize();
	void generateMessages();
	void processAMessage(Message* pMessage);
};

#endif

