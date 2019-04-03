// 
// 
// 

#include "MemoryManager.h"
#include "Globals.h"
#include "Message.h"

MemoryManager::MemoryManager() {
	freeStoreHead = 0;
	expandPoolSize();
}

MemoryManager::~MemoryManager() {
	cleanUp();
}

inline void* MemoryManager::allocate(size_t size)
{
	if (0 == freeStoreHead) {
		expandPoolSize();
	}

	FreeStore* head = this->freeStoreHead;
	freeStoreHead = head->next;
	return head;
}

inline void MemoryManager::free(void* deleted)
{
	FreeStore* head = static_cast <FreeStore*> (deleted);
	head->next = this->freeStoreHead;
	freeStoreHead = head;
}

void MemoryManager::expandPoolSize()
{
	size_t size = (sizeof(Message) > sizeof(FreeStore*)) ? sizeof(Message) : sizeof(FreeStore*);
	FreeStore* head = reinterpret_cast <FreeStore*> (new char[size]);
	this->freeStoreHead = head;

	for (int i = 0; i < MJUC_POLLSIZE_OF_MEMORY_MANAGER; i++) {
		head->next = reinterpret_cast <FreeStore*> (new char[size]);
		head = head->next;
	}
	head->next = 0;
}

void MemoryManager::cleanUp()
{
	FreeStore* nextPtr = this->freeStoreHead;
	for (; nextPtr; nextPtr = freeStoreHead) {
		this->freeStoreHead = this->freeStoreHead->next;
		delete[] nextPtr;
	}
}