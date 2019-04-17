// Illuminant.h

#ifndef _ILLUMINANT_h
#define _ILLUMINANT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Component.h"
#include "AnalogInputChannel.h"
#include "PhotoResistor.h"

class Illuminant: public Component
{
public:
	enum ELightState {
		eBright,
		eDark,
		eNumLightStates
	};
protected:
	AnalogInputChannel* pChannelPhotoResistor_;
	PhotoResistor* pPhotoResistor_;
	int cdsLight_;

public:
	Illuminant();
	~Illuminant();
	void initialize();
	void finalize();
	void generateMessages();
	void processAMessage(Message* pMessage);
};

#endif