// EArray.h

#ifndef _EARRAY_h
#define _EARRAY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "EGlobal.h"

template<typename Element, unsigned int size = DEFAULT_SIZE_OF_EARRAY>
class EArray
{
public:
	class Iterator {
	private:
		Element* pIndex;
	public:
		Iterator(Element* pIndex = 0) : pIndex(pIndex) {}
		bool operator!=(const Iterator& iter) { return this->pIndex != iter.pIndex; }
		bool operator==(const Iterator& iter) { return this->pIndex == iter.pIndex; }
		Iterator& operator++() { ++(this->pIndex); return (*this); }
		const Iterator operator++(int) { Iterator returnValue(*this); (this->pIndex)++; return returnValue; }
		Element operator*() { return *(this->pIndex); }
		Element* getPIndex() { return this->pIndex; }
	};
private:
	Element buffer[size];
	unsigned int count;
	Iterator iterBegin;
	Iterator iterEnd;
public:
	EArray() {
		this->count = 0;
		this->iterBegin = Iterator(this->buffer);
		this->iterEnd = Iterator(this->buffer);
	}
	~EArray() {}

	unsigned int getCount() { return this->count; }
	bool add(Element element) {
		if (this->count < size) {
			this->buffer[(this->count)++] = element;
			++(this->iterEnd);
			return true;
		}
		ELOG(ELOG_ERROR, "EArray.add()", "Too many element");
		return false;
	}

	Iterator begin() { return this->iterBegin;}
	Iterator end() { return this->iterEnd;}

	Element& operator[](unsigned int index) {
		if ((index >= 0) && (index < this->count)) {
			return this->buffer[index];
		}
		ELOG(ELOG_ERROR, "EArray.[]", "Out of index");
		return NULL;
	}

	void clear() {
		this->count = 0;
		this->iterBegin = Iterator(this->buffer);
		this->iterEnd = Iterator(this->buffer);
	}
};

#endif