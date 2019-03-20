// PiezoSpeaker.h

#ifndef _PIEZOSPEAKER_h
#define _PIEZOSPEAKER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Speaker.h"

#define _DELAY_BT_NOTES 400

class PiezoSpeakerClass : public SpeakerClass
{
 protected:
	 int m_outPin;
	 int m_delayBTNotes = _DELAY_BT_NOTES;

 public:
	void init();
	void init(int outPin);
	bool process();
	bool operate();
};

extern PiezoSpeakerClass PiezoSpeaker;

#endif

