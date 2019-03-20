// Speaker.h

#ifndef _SPEAKER_h
#define _SPEAKER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Actuator.h"

class SpeakerClass : public ActuatorClass
{
 protected:


 public:
	virtual void init();
	virtual bool process();
	virtual bool operate();
};

extern SpeakerClass Speaker;

#endif

