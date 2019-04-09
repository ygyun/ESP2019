// Main.h

#ifndef _MAIN_h
#define _MAIN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Main
{
public:
	Main();
	~Main();
	void initialize();
	void finalize();
	void run();
};

#endif

