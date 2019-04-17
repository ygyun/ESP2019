// MemoryManager.h

#ifndef _MEMORYMANAGER_h
#define _MEMORYMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Globals.h"

class MemoryManager
{
public:
	struct FreeStore {
		FreeStore* next;
	};

private:
	FreeStore* freeStoreHead_;
	size_t size_;

public:
	MemoryManager(size_t size);
	~MemoryManager();
	void* allocate();
	void free(void* deleted);
	void expandPoolSize();
	void cleanUp();
};

#endif

