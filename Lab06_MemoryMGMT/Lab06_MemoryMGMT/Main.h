// Main.h

#ifndef _MAIN_h
#define _MAIN_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "LEDManager.h"

class Main
{
private:
	LEDManager ledManager;

public:
	Main() {}
	~Main() {}

	void initialize() {
		this->ledManager.initialize();
	}

	void finalize() {
		this->ledManager.finalize();
	}

	void run() {
		while (true) {
			this->ledManager.run();
		}
	}
};

#endif