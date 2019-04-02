// Illuminant.h

#ifndef _ILLUMINANT_h
#define _ILLUMINANT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "SimpleSensor.h"
#include "Channel.h"

class Illuminant: public SimpleSensor
{
public:
	enum EState {
		eReady,
		eRunning,
		eNumStates
	};
	enum EChannelId {
		eIdCDS,
		eNumChannelIds
	};

private:
	EState eState;
	Channel *pChannels[eNumChannelIds];
	int cdsLight_;

public:
	Illuminant(EChannelId eIdCDS, Channel *pIlluminatChannel);
	~Illuminant();
	void initialize();
	void finalize();
	void start();
	bool wait();
	int getCDSLight();
};

#endif

