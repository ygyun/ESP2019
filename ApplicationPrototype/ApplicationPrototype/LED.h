// LED.h

#ifndef _LED_h
#define _LED_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Component.h"
#include "PWMOutputChannel.h"
#include "RGBLED.h"
#include "Illuminant.h"
#include "Proximity.h"

class LED: public Component
{
public:
	typedef struct _RBGValue {
		int _R;
		int _G;
		int _B;
	} RGBValue;
private:
	PWMOutputChannel* pChannelrgbLEDRed_;
	PWMOutputChannel* pChannelrgbLEDGreen_;
	PWMOutputChannel* pChannelrgbLEDBlue_;
	RGBLED* pRGBbLED_;
	RGBValue rgbValues[Illuminant::ELightState::eNumLightStates][Proximity::EDistanceState::eNumDistanceStates];
	int indexI_;
	int indexJ_;

public:
	LED();
	~LED();
	void initialize();
	void finalize();
	void generateMessages();
	void processAMessage(Message* pMessage);
};

#endif

