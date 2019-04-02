/*
 Name:		Lab05_StateNHAL.ino
 Created:	2019-03-28 오후 2:47:21
 Author:	BCDev
*/

// the setup function runs once when you press reset or power the board
#include "RGBLED.h"
#include "LEDManager.h"
#include "UltrasonicWave.h"
#include "Illuminant.h"
#include "Illuminant.h"
#include "SimpleSensor.h"
#include "UltrasonicWave.h"
#include "TRSensor.h"
#include "Actuator.h"
#include "Sensor.h"
#include "Component.h"
#include "Main.h"

static Main main;

void setup() {
	main.initialize();
}

// the loop function runs over and over again until power down or reset
void loop() {
	main.run();  
}
