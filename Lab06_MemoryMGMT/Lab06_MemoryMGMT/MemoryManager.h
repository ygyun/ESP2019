// MemoryManager.h

#ifndef _MEMORYMANAGER_h
#define _MEMORYMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class MemoryManager
{
public:
	struct FreeStore {
		FreeStore* next;
	};
private:
	FreeStore* freeStoreHead;
public:
	MemoryManager();
	~MemoryManager();
	void* allocate(size_t size);
	void free(void* deleted);
	void expandPoolSize();
	void cleanUp();
};

#endif

