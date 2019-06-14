// EPhotoResistor.h

#ifndef _EPHOTORESISTOR_h
#define _EPHOTORESISTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "EChannel.h"

class EPhotoResistor
{
public:
	enum EChannelId {
		eIdCDS,
		eNumChannelIds
	};

private:
	EChannel *pChannels[eNumChannelIds];
	int cdsLight;

public:
	EPhotoResistor(EChannelId eIdCDS, EChannel *pPhotoResistorChannel) {
		this->pChannels[eIdCDS] = pPhotoResistorChannel;
	}
	~EPhotoResistor() {}
	void initialize() {}
	void finalize() {}
	int read() {
		return this->cdsLight = this->pChannels[eIdCDS]->read();
	}
};

#endif

