// EMessage.h

#ifndef _EMESSAGE_h
#define _EMESSAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "EGlobal.h"
#include "EMemoryManager.h"

class EComponent;

static unsigned int messageID = 0;

class EMessage {
private:
	unsigned int ID_;
	unsigned int type_;
	EComponent* pTarget_;
	EComponent* pSource_;
	int iArg_;
	void* pArg_;
public:
	static EMemoryManager<EMessage> memoryManager;
	EMessage() {}
	EMessage(unsigned int type, EComponent* pTarget, EComponent* pSource, int iArg = 0, void* pArg = NULL) :
		ID_(++messageID),
		type_(type),
		pTarget_(pTarget),
		pSource_(pSource),
		iArg_(iArg),
		pArg_(pArg) {}

	~EMessage() {}
	unsigned int getType() { return this->type_; }
	EComponent* getPTarget() { return this->pTarget_; }
	EComponent* getPSource() { return this->pSource_; }
	int getIArg() { return this->iArg_; }
	void* getPArg() { return this->pArg_; }
	void* operator new (size_t size) {
		return memoryManager.allocate();
	}

	void operator delete (void* pointerToDelete) {
		memoryManager.free(pointerToDelete);
	}
};

#endif