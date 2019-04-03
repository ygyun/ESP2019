// 
// 
// 

#include "Message.h"
#include "MemoryManager.h"

extern MemoryManager gMemoryManager;

Message::Message(int id, int state) : id_(id), state_(state) {}

Message::~Message() {}

void* Message::operator new (size_t size) {
	return gMemoryManager.allocate(size);
}

void Message::operator delete (void* pointerToDelete) {
	gMemoryManager.free(pointerToDelete);
}
