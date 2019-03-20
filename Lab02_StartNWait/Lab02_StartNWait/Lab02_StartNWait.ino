/*
 Name:		Lab02_StartNWait.ino
 Created:	2019-03-19 오후 2:12:00
 Author:	BCDev
*/

// the setup function runs once when you press reset or power the board
#include "PiezoSpeaker.h"
#include "ServoMotor.h"
#include "RGBLED.h"
#include "LCD.h"
#include "Proximity.h"
#include "Illuminant.h"
#include "ActSensor.h"
#include "Actuator.h"
#include "Sensor.h"
#include "Device.h"
#include "Main.h"

static Main main;

void setup() {
	main.init();
}

// the loop function runs over and over again until power down or reset
void loop() {
	main.run();
}
