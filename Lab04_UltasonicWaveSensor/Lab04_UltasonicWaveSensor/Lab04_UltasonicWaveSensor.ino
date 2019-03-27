/*
 Name:		Lab04_UltasonicWaveSensor.ino
 Created:	2019-03-27 오후 6:37:50
 Author:	BCDev
*/

// the setup function runs once when you press reset or power the board
#include "Channel.h"
#include "Actuator.h"
#include "Sensor.h"
#include "Domain.h"
#include "AutoDoorWithLighting.h"
#include "Main.h"

static Main main;

void setup() {
	main.initialize();
}

// the loop function runs over and over again until power down or reset
void loop() {
	main.run();  
}
