// 
// 
// 

#include "MemoryManager.h"

MemoryManager::MemoryManager(size_t size): size_(size), freeStoreHead_(0) {}

MemoryManager::~MemoryManager() {
	cleanUp();
}

inline void* MemoryManager::allocate()
{
	if (0 == freeStoreHead_) {
		expandPoolSize();
	}

	FreeStore* head = this->freeStoreHead_;
	freeStoreHead_ = head->next;
	return head;
}

inline void MemoryManager::free(void* deleted)
{
	FreeStore* head = static_cast <FreeStore*> (deleted);
	head->next = this->freeStoreHead_;
	freeStoreHead_ = head;
}

void MemoryManager::expandPoolSize()
{
	size_t size = (this->size_ > sizeof(FreeStore*)) ? this->size_ : sizeof(FreeStore*);
	FreeStore* head = reinterpret_cast <FreeStore*> (new char[size]);
	this->freeStoreHead_ = head;

	for (int i = 0; i < MJUC_POLLSIZE_OF_MEMORY_MANAGER; i++) {
		head->next = reinterpret_cast <FreeStore*> (new char[size]);
		head = head->next;
	}
	head->next = 0;
}

void MemoryManager::cleanUp()
{
	FreeStore* nextPtr = this->freeStoreHead_;
	for (; nextPtr; nextPtr = freeStoreHead_) {
		this->freeStoreHead_ = this->freeStoreHead_->next;
		delete[] nextPtr;
	}
}
