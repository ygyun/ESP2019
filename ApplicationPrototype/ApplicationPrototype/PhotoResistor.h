// PhotoResistor.h

#ifndef _PHOTORESISTOR_h
#define _PHOTORESISTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Channel.h"

class PhotoResistor
{
public:
	enum EChannelId {
		eIdCDS,
		eNumChannelIds
	};

private:
	Channel* pChannels_[eNumChannelIds];

public:
	PhotoResistor(EChannelId eIdCDS, Channel *pChannelPhotoResistor);
	~PhotoResistor();
	void initialize();
	void finalize();
	int read();
};

#endif

