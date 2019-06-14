// EMessage.h

#ifndef _EMESSAGE_h
#define _EMESSAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "EMemoryManager.h"

class EComponent;

static unsigned long long messageID = 0;

class EMessage {
private:
	unsigned long long ID;
	unsigned int type;
	EComponent* pTarget;
	EComponent* pSource;
	int iArg;
	void* pArg;
public:
	static EMemoryManager memoryManager;
	EMessage() {}
	EMessage(unsigned int type, EComponent* pTarget, int iArg = 0, void* pArg = NULL) :
		ID(++messageID),
		type(type),
		pTarget(pTarget),
		iArg(iArg),
		pArg(pArg) {}
	EMessage(unsigned int type, EComponent* pTarget, EComponent* pSource, int iArg = 0, void* pArg = NULL) :
		ID(++messageID),
		type(type),
		pTarget(pTarget),
		pSource(pSource),
		iArg(iArg),
		pArg(pArg) {}
	~EMessage() {}
	unsigned int getType() {return this->type;}
	EComponent* getPTarget() {return this->pTarget;}
	EComponent* getPSource() {return this->pSource;}
	int getIArg() {return this->iArg;}
	void* getPArg() {return this->pArg;}

	void* operator new (size_t size) {
		return memoryManager.allocate();
	}

	void operator delete (void* pointerToDelete) {
		memoryManager.free(pointerToDelete);
	}
};

#endif