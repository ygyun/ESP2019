// Main.h

#ifndef _MAIN_h
#define _MAIN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Domain.h"

class Main {
private:
	Domain domain;

public:
	// constructors & destructors
	Main() {}
	~Main() {}
	void initialize() {
		this->domain.initialize();
	}
	void finalize() {
		this->domain.finalize();
	}

	// methods
	void run() {
		unsigned long prev, cur, diff;
		cur = 0;

		while (true)
		{
			prev = cur;
			cur = millis();
			diff = cur - prev;

			this->domain.run();

			Serial.print("   Cur: ");
			Serial.print(cur);
			Serial.print("   diff: ");
			Serial.print(diff);
			Serial.println("");

			delay(10);
		}
	}
};
#endif

