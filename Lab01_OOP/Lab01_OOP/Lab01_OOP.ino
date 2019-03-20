﻿/*
 Name:		LabMarch.ino
 Created:	2019-03-18 오전 8:46:13
 Author:	BCDev
*/

// the setup function runs once when you press reset or power the board

#include "ServoMotor.h"
#include "PiezoSpeaker.h"
#include "RGBLED.h"
#include "Speaker.h"
#include "Motor.h"
#include "LED.h"
#include "LCD.h"
#include "Actuator.h"
#include "IlluminantSensor.h"
#include "ProximitySensor.h"
#include "Sensor.h"

int QUEUE_DistanceInCM;
int QUEUE_CDSLight;
String QUEUE_StringOne;
String QUEUE_StringTwo;

void setup() {
	ProximitySensor.init(6, 7, 10);
	IlluminantSensor.init(0);
	LCD.init(12, 11, 2, 3, 4, 5);
	RGBLED.init(13, 10, 0);
	PiezoSpeaker.init(8);
	ServoMotor.init(9);
}

// the loop function runs over and over again until power down or reset
void loop() {
	if (!ProximitySensor.sense())
	{
		Serial.println("ProximitySenser error");
	}
	if (!IlluminantSensor.sense())
	{
		Serial.println("IlluminantSensor error");
	}

	LCD.process();
	LCD.operate();

	RGBLED.process();
	RGBLED.operate();

	if (PiezoSpeaker.process())
	{
		PiezoSpeaker.operate();
	}

	if (ServoMotor.process())
	{
		ServoMotor.operate();
	}
}