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

#define TIMER_TIMEOUT				1000
#define TIMER_TIMEOUT_ILLUMINANT	1000
#define TIMER_TIMEOUT_DISTANCE		1500

#define DEFAULT_SIZE_OF_EARRAY	16
#define DEFAULT_SIZE_OF_EQUEUE	16
#define DEFAULT_NUM_BLOCKS_OF_MEMORY_MANAGER	16

// 조도 센서
#define	MJUC_CHANNEL_ILLUMINANT						0

// 초음파 거리 센서
#define MJUC_CHANNEL_ULTRASONIC_WAVE_TRANSMITTER	7
#define MJUC_CHANNEL_ULTRASONIC_WAVE_RECEIVER		6
#define MJUC_TIME_OUT_OF_MEASURING_IN_MICROSECOND	1000000
#define MJUC_DIVISOR_FOR_DISTANCE_CALCULATION		58.2		// 초음파 속도: 340m/s

// RGBLED
#define MJUC_CHANNEL_RGBLED_RED						3
#define MJUC_CHANNEL_RGBLED_GREEN					10
#define MJUC_CHANNEL_RGBLED_BLUE					5
#define MJUC_LED_STRENGTH_STRONG					255
#define MJUC_LED_STRENGTH_WEAK						50

// 거리구분(cm)
#define MJUC_DISTANCE_TOO_CLOSE						3	// < 3cm
#define MJUC_DISTANCE_VERY_CLOSE					5	
#define MJUC_DISTANCE_CLOSE							8	
#define MJUC_DISTANCE_FAR							10	
#define MJUC_DISTANCE_VERY_FAR						15

// 밝기구분(CDS 저항 0~1023)
#define MJUC_LIGHT_DISTINCTION						800
#endif
