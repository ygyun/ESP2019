// 
// 
// 

#include "Message.h"

extern MemoryManager* fsMM;
int Message::iCount_ = 0;

Message::Message(EMessageType messageType, Component* pTargetComponent, Component* pSourceComponent, void* pArgument):
	messageID_(++iCount_),
	messageType_(messageType),
	pTargetComponent_(pTargetComponent),
	pSourceComponent_(pSourceComponent),
	pArgument_(pArgument) {}

Message::~Message() {}

void* Message::operator new (size_t size) {
	return fsMM->allocate();
}

void Message::operator delete (void* pointerToDelete) {
	fsMM->free(pointerToDelete);
}