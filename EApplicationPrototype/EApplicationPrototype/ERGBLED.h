// ERGBLED.h

#ifndef _ERGBLED_h
#define _ERGBLED_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "EChannel.h"

class ERGBLED
{
public:
	enum EChannelId {
		eIdRed,
		eIdGreen,
		eIdBlue,
		eNumChannelIds
	};
private:
	EChannel *pChannels[eNumChannelIds];
public:
	ERGBLED(EChannelId eIdRed, EChannel *pChannelRed,
		EChannelId eIdGreen, EChannel *pChannelGreen,
		EChannelId eIdBlue, EChannel *pChannelBlue) {
		this->pChannels[eIdRed] = pChannelRed;
		this->pChannels[eIdGreen] = pChannelGreen;
		this->pChannels[eIdBlue] = pChannelBlue;
	}
	~ERGBLED() {}
	void initialize() {}
	void finalize() {}
	void write(int red, int green, int blue) {
		this->pChannels[eIdRed]->write(red);
		this->pChannels[eIdGreen]->write(green);
		this->pChannels[eIdBlue]->write(blue);
	}
	void writeRed(int red) { this->pChannels[eIdRed]->write(red); }
	void writeGreen(int green) { this->pChannels[eIdGreen]->write(green); }
	void writeBlue(int blue) { this->pChannels[eIdBlue]->write(blue); }
};

#endif

