// LEDManager.h

#ifndef _LEDMANAGER_h
#define _LEDMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Component.h"
#include "AnalogInputChannel.h"
#include "DigitalInputChannel.h"
#include "DigitalOutputChannel.h"
#include "PWMOutputChannel.h"
#include "Illuminant.h"
#include "UltrasonicWave.h"
#include "RGBLED.h"

class LEDManager: public Component
{
private:
	AnalogInputChannel illuminantChannel;

	DigitalOutputChannel ultrasonicWaveChannelTransmitter;
	DigitalInputChannel ultrasonicWaveChannelReceiver;

	PWMOutputChannel rgbLEDchannelRed;
	PWMOutputChannel rgbLEDchannelGreen;
	PWMOutputChannel rgbLEDchannelBlue;

	Illuminant illuminant;
	UltrasonicWave ultrasonicWave;

	RGBLED rgbLED;

public:
	LEDManager();
	~LEDManager();
	void initialize();
	void finalize();
	void process();
	void actuate();
	void run();
};

#endif

