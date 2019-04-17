/*
 Name:		ApplicationPrototype.ino
 Created:	2019-04-09 오후 3:18:03
 Author:	BCDev
*/

// the setup function runs once when you press reset or power the board
#include "LEDManagerWithLIghtNDistance.h"
#include "UltrasonicWave.h"
#include "Proximity.h"
#include "RGBLED.h"
#include "LED.h"
#include "PhotoResistor.h"
#include "Illuminant.h"
#include "Scheduler.h"
#include "Message.h"
#include "Component.h"
#include "Main.h"
#include "MemoryManager.h"

Main* pApplicationPrototype;
MemoryManager* pMMofMessage;

void setup() {
	pApplicationPrototype = new Main();
}

// the loop function runs over and over again until power down or reset
void loop() {
	pApplicationPrototype->initialize();
	pApplicationPrototype->run();
	pApplicationPrototype->finalize();

	delete pApplicationPrototype;
}
