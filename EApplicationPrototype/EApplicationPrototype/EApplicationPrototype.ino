/*
 Name:		EApplicationPrototype.ino
 Created:	2019-04-25 오후 4:39:15
 Author:	BCDev
*/

// the setup function runs once when you press reset or power the board
#include "EMain.h"
#include "ETimer.h"
#include "EDummyReceiver.h"
#include "EDummySender.h"
#include "ELifeCycleManager.h"
#include "EScheduler.h"
#include "EComponent.h"
#include "EMemoryManager.h"
#include "EMessage.h"
#include "EArray.h"
#include "EQueue.h"

EMain main;

void setup() {
	main.initialize();
}

// the loop function runs over and over again until power down or reset
void loop() {
	main.run();
}
