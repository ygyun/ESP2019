#ifndef _EGLOBAL_h
#define _EGLOBAL_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <stdint.h>

#define DEFINE_CLASS(class_name) \
    class class_name { \
    public: \
        virtual uint32_t getID() { return hash(#class_name); } \


uint32_t hash(const char *str)
{
	unsigned long hash = 5381;
	int c;

	while ((c = *str++))
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}

/*
DEFINE_CLASS(MyTest)

MyTest() {};
~MyTest() {};
};

DEFINE_CLASS(MyCTest : public MyTest)

MyCTest() {};
~MyCTest() {};
};
*/

template<typename T>
struct TypeID
{
	static size_t get()
	{
		return reinterpret_cast<size_t>(&ch);
	}
private:
	static char ch;
};

template<typename T>
char TypeID<T>::ch;


class A {}
class B {}

TypeID<A> tidA;
TypeID<B> tidB;

tidA.get();
tidB.get();

#endif
