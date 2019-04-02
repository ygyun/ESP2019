// RGBLED.h

#ifndef _RGBLED_h
#define _RGBLED_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Actuator.h"
#include "Channel.h"

class RGBLED: public Actuator
{
public:
	enum EState {
		eReady,
		eRunning,
		eNumStates
	};
	enum EChannelId {
		eIdRed,
		eIdGreen,
		eIdBlue,
		eNumChannelIds
	};
private:
	EState eState;
	Channel *pChannels[eNumChannelIds];
	struct _RBGValue {
		int _R;
		int _G;
		int _B;
	} rgbValue;
public:
	RGBLED(EChannelId eIdRed, Channel *pChannelRed,
		   EChannelId eIdGreen, Channel *pChannelGreen,
		   EChannelId eIdBlue, Channel *pChannelBlue);
	~RGBLED();
	void initialize();
	void finalize();
	void start();
	bool wait();
	void setRGBValue(int R, int G, int B);
};

#endif

