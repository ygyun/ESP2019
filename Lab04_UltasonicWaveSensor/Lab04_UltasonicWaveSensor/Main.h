// Main.h

#ifndef _MAIN_h
#define _MAIN_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "AutoDoorWithLighting.h"

class Main
{
private:
	AutoDoorWithLighting autoDoorWithLighting;

public:
	Main() {}

	~Main() {}

	void initialize() {
		this->autoDoorWithLighting.initialize();
	}

	void finalize() {
		this->autoDoorWithLighting.finalize();
	}

	void run() {
		unsigned long prev, cur, diff;
		cur = 0;

		while (true)
		{
			this->autoDoorWithLighting.run();

			//prev = cur;
			//cur = micros();
			//diff = cur - prev;
			//Serial.print("   Cur: ");
			//Serial.print(cur);
			//Serial.print("   diff: ");
			//Serial.println(diff);
		}
	}
};

#endif