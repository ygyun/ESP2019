// EMemoryManager.h

#ifndef _EMEMORYMANAGER_h
#define _EMEMORYMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

template<typename Element>
class EMemoryManager
{
public:
	struct FreeStore {
		FreeStore* next;
	};

private:
	FreeStore* freeStoreHead_;
//	FreeStore* freeStrorHead_ = char[sizeof(Element)* size];

public:
	EMemoryManager(int numBlocks = 32){
		size_t size = (sizeof(Element) > sizeof(FreeStore*)) ? sizeof(Element) : sizeof(FreeStore*);
		FreeStore* head = reinterpret_cast <FreeStore*> (new char[size]);
		this->freeStoreHead_ = head;

		for (int i = 0; i < numBlocks; i++) {
			head->next = reinterpret_cast <FreeStore*> (new char[size]);
			head = head->next;
		}
		head->next = 0;
	}

	~EMemoryManager() { cleanUp(); }

	void* allocate() {
		FreeStore* head = this->freeStoreHead_;
		freeStoreHead_ = head->next;
		return head;
	}

	void free(void* deleted) {
		FreeStore* head = static_cast <FreeStore*> (deleted);
		head->next = this->freeStoreHead_;
		freeStoreHead_ = head;
	}

	void cleanUp() {
		FreeStore* nextPtr = this->freeStoreHead_;
		for (; nextPtr; nextPtr = freeStoreHead_) {
			this->freeStoreHead_ = this->freeStoreHead_->next;
			delete[] nextPtr;
		}
	}
};

#endif