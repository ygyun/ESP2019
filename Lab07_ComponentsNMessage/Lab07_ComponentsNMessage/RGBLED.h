// RGBLED.h

#ifndef _RGBLED_h
#define _RGBLED_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class RGBLEDClass
{
public:
	enum EChannelId {
		eIdRed,
		eIdGreen,
		eIdBlue,
		eNumChannelIds
	};
	typedef struct _RBGValue {
		int _R;
		int _G;
		int _B;
	} RGBValue;

private:
	Channel *pChannels_[eNumChannelIds];
	int eLishtStateIndex_;
	int eDistanceStateIndex_;
	RGBValue rgbValues_[ELightState::eNumLightStates][EDistanceState::eNumDistanceStates];
public:
	RGBLED(EChannelId eIdRed, Channel *pChannelRed,
		EChannelId eIdGreen, Channel *pChannelGreen,
		EChannelId eIdBlue, Channel *pChannelBlue);
	~RGBLED();
	void initialize();
	void finalize();
	void actuate();
	void setState(int eLishtStateIndex, int eDistanceStateIndex);

};

extern RGBLEDClass RGBLED;

#endif

