/*
 Name:		Lab06_MemoryMGMT.ino
 Created:	2019-04-02 오후 1:38:37
 Author:	BCDev
*/

// the setup function runs once when you press reset or power the board
#include "Main.h"
#include "MemoryManager.h"
#include "Message.h"

static MemoryManager gMemoryManager;
static Main myMain;

void setup() {
	myMain.initialize();
}

// the loop function runs over and over again until power down or reset
void loop() {
	myMain.run();
}