// 
// 
// 

#include "Component.h"
#include "Message.h"
#include "MemoryManager.h"

extern MemoryManager* pMMofMessage;
int Message::iCount_ = 0;

Message::Message(int messageType, Component* pSourceComponent, Component* pTargetComponent, UValue uArgument):
	messageID_(++iCount_),
	messageType_(messageType),
	pSourceComponent_(pSourceComponent),
	pTargetComponent_(pTargetComponent),
	uArgument_(uArgument) {}

Message::~Message() {}

void* Message::operator new (size_t size) {
	return pMMofMessage->allocate();
}

void Message::operator delete (void* pointerToDelete) {
	pMMofMessage->free(pointerToDelete);
}