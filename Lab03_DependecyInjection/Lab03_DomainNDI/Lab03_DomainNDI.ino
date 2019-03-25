/*
 Name:		Lab03_DomainNDI.ino
 Created:	2019-03-21 오후 2:16:13
 Author:	BCDev
*/

#include "Proximity.h"
#include "Actuator.h"
#include "RGBLED.h"
#include "Illuminant.h"
#include "Channel.h"
#include "Sensor.h"
#include "Domain.h"
#include "Main.h"

static Main main;

// the setup function runs once when you press reset or power the board
void setup() {
	main.initialize();
}

// the loop function runs over and over again until power down or reset
void loop() {
	main.run();
}