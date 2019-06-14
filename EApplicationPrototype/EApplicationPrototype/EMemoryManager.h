// EMemoryManager.h

#ifndef _EMEMORYMANAGER_h
#define _EMEMORYMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "EGlobal.h"

class EMemoryManager
{
public:
	struct FreeStore {
		FreeStore* next;
	};

private:
	FreeStore* freeStoreHead;

public:
	static EMemoryManager messageMemoryManager;
	EMemoryManager(size_t size, int numBlocks = DEFAULT_NUM_BLOCKS_OF_MEMORY_MANAGER) {
		if (size < sizeof(FreeStore*)) {
			size = sizeof(FreeStore*);
		}
		FreeStore* head = reinterpret_cast <FreeStore*> (new char[size]);
		this->freeStoreHead = head;

		for (int i = 0; i < numBlocks; i++) {
			head->next = reinterpret_cast <FreeStore*> (new char[size]);
			head = head->next;
		}
		head->next = 0;
	}

	~EMemoryManager() {
		FreeStore* nextPtr = this->freeStoreHead;
		for (; nextPtr; nextPtr = freeStoreHead) {
			this->freeStoreHead = this->freeStoreHead->next;
			delete[] nextPtr;
		}
	}

	void* allocate() {
		FreeStore* head = this->freeStoreHead;
		freeStoreHead = head->next;
		return head;
	}

	void free(void* deleted) {
		FreeStore* head = static_cast <FreeStore*> (deleted);
		head->next = this->freeStoreHead;
		freeStoreHead = head;
	}
};

#endif