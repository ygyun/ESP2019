// Main.h

#ifndef _MAIN_h
#define _MAIN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Device.h"
#include "Illuminant.h"
#include "Proximity.h"
#include "LCD.h"
#include "RGBLED.h"
#include "ServoMotor.h"
#include "PiezoSpeaker.h"

#define MAX_NUM_DEVICES	6

class Main
{
private:
	Device* arrDevice[MAX_NUM_DEVICES];

	Illuminant illuminant;
	Proximity proximity;

	LCD lcd;
	RGBLED rgbLED;
	ServoMotor servoMotor;
	PiezoSpeaker piezoSpeaker;

 public:
	Main();
	void init();
	void run();
};

#endif

