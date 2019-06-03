#ifndef _EGLOBAL_h
#define _EGLOBAL_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#define ELOG_LEVEL	3
#define ELOG_FATAL	1
#define ELOG_ERROR	2
#define ELOG_INFO	3
#define ELOG_DEBUG	4
#define ELOG_ALL	5

#if defined(ELOG_LEVEL)
#define ELOG(level,comment,arg) \
	if((ELOG_LEVEL) >= (level)) {\
		Serial.print(millis());\
		Serial.print(" ");\
		Serial.print((#level));\
		Serial.print(" ");\
		Serial.print((comment));\
		Serial.print(" ");\
		Serial.println((arg));\
		Serial.flush();\
	}
#else
#define ELOG(level,comment,arg) 
#endif

#define TIMER_TIMEOUT	1000

#define DEFAULT_SIZE_OF_EARRAY	32
#define DEFAULT_SIZE_OF_EQUEUE	32
#define DEFAULT_NUM_BLOCKS_OF_MEMORY_MANAGER	32

#endif
