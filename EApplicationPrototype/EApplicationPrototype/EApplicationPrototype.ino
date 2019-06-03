/*
 Name:		EApplicationPrototype.ino
 Created:	2019-04-25 오후 4:39:15
 Author:	BCDev
*/

// the setup function runs once when you press reset or power the board
#include "EMain.h"

static EMain simpleMain;

void setup() {
	simpleMain.initializeAsMain();
}

// the loop function runs over and over again until power down or reset
void loop() {
	simpleMain.runAsMain();
}