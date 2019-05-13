// EArray.h

#ifndef _EARRAY_h
#define _EARRAY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

template<typename Element, unsigned int size=32>
class EArray
{
public:
	class Iterator {
	private:
		Element* pIndex_;
	public:
		Iterator(Element* pIndex = 0) : pIndex_(pIndex) {}
		bool operator!=(const Iterator& iter) { return this->pIndex_ != iter.pIndex_; }
		bool operator==(const Iterator& iter) { return this->pIndex_ == iter.pIndex_; }
		Iterator& operator++() { ++(this->pIndex_); return (*this); }
		const Iterator operator++(int) { Iterator return_value(*this); (this->pIndex_)++; return return_value; }
		Element operator*() { return (*this->pIndex_); }
	};
private:
	Element buffer_[size];
	unsigned int count_;
	Iterator iterBegin_;
	Iterator iterEnd_;
public:
	EArray() {
		this->count_ = 0;
		this->iterBegin_ = Iterator(this->buffer_);
		this->iterEnd_ = Iterator(this->buffer_);
	}

	~EArray() {}

	bool add(Element element) {
		if (this->count_ < size) {
			this->arr_[(this->count_)++] = element;
			++(this->iterEnd_);
			return true;
		}
		return false;
	}

	Iterator begin() { return this->iterBegin_; }
	Iterator end() { return this->iterEnd_; }

	Element& operator[](int index) {
		if ((index >= 0) && (index < this->count_)) {
			return this->buffer_[index];
		}
		return NULL;
	}
};

#endif

