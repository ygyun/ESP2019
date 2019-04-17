// LEDManagerWithLIghtNDistance.h

#ifndef _LEDMANAGERWITHLIGHTNDISTANCE_h
#define _LEDMANAGERWITHLIGHTNDISTANCE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Component.h"

class LEDManagerWithLIghtNDistance: public Component
{
public:
	LEDManagerWithLIghtNDistance();
	~LEDManagerWithLIghtNDistance();
	void initialize();
	void finalize();
	void generateMessages();
	void processAMessage(Message* pMessage);
};

#endif

