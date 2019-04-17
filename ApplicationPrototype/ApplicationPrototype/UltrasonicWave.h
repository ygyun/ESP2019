// UltrasonicWave.h

#ifndef _ULTRASONICWAVE_h
#define _ULTRASONICWAVE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Channel.h"

class UltrasonicWave
{
public:
	enum EState {
		eReady,
		eRunning,
		eWaitForDeviceReady,
		eMeasuringReady,
		eWaitForMeasuring,
		eMeasuring,
		eNumStates
	};
	enum EChannelId {
		eIdTransmitter,
		eIdReceiver,
		eNumChannelIds
	};
private:
	EState eState_;
	Channel *pChannels_[eNumChannelIds];
	long initialTime_;
	long startTime_;
	long elapsedTime_;
public:
	UltrasonicWave(EChannelId eIdTransmitter, Channel *pChannelTransmitter,
		EChannelId eIdReceiver, Channel *pChannelReceiver);
	~UltrasonicWave();
	void initialize();
	void finalize();
	int read();
};

#endif

