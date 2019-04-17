// Main.h

#ifndef _MAIN_h
#define _MAIN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Scheduler.h"

class Main: public Scheduler
{
private:
	Scheduler* pScheduler_;
public:
	Main();
	~Main();
	void initialize();
	void finalize();
	void run();
	void generateMessages();
	void processAMessage(Message* pMessage);
};

#endif

