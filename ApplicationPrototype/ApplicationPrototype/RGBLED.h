// RGBLED.h

#ifndef _RGBLED_h
#define _RGBLED_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Channel.h"
#include "Message.h"

class RGBLED
{
public:
	enum EChannelId {
		eIdRed,
		eIdGreen,
		eIdBlue,
		eNumChannelIds
	};

private:
	Channel* pChannels_[eNumChannelIds];

public:
	RGBLED(EChannelId eIdRed, Channel *pChannelRed,
		EChannelId eIdGreen, Channel *pChannelGreen,
		EChannelId eIdBlue, Channel *pChannelBlue);
	~RGBLED();
	void initialize();
	void finalize();
	void write(int R, int G, int B);
};

#endif

