/*
 Name:		Lab07_ComponentsNMessage.ino
 Created:	2019-04-04 오후 5:02:43
 Author:	BCDev
*/

#include "RGBLED.h"
#include "MessageQueue.h"
#include "Queue.h"
#include "MessageQueue.h"
#include "Illuminant.h"
#include "MemoryManager.h"
#include "IlluminantManager.h"
#include "Message.h"
#include "Component.h"
#include "Main.h"
#include "MemoryManager.h"

Main* myMain;
MemoryManager* MMofMessage;
MessageQueue* pMessageQueue;

// the setup function runs once when you press reset or power the board
void setup() {
	myMain = new Main();
	MMofMessage = new MemoryManager(sizeof(Message));
	pMessageQueue = new MessageQueue(MJUC_POLLSIZE_OF_MEMORY_MANAGER);
}

// the loop function runs over and over again until power down or reset
void loop() {
	myMain->initialize();
	myMain->run();
	myMain->finalize();
}