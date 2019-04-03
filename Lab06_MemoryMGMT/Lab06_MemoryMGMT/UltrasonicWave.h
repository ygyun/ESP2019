// UltrasonicWave.h

#ifndef _ULTRASONICWAVE_h
#define _ULTRASONICWAVE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "TRSensor.h"
#include "Channel.h"

class UltrasonicWave: public TRSensor
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
	EState eState;
	Channel *pChannels[eNumChannelIds];
	unsigned long initialTime_;
	unsigned long startTime_;
	unsigned long elapsedTime_;
	unsigned long prevElapsedTime_;
public:
	UltrasonicWave(EChannelId eIdTransmitter, Channel *pChannelTransmitter,
				   EChannelId eIdReceiver, Channel *pChannelReceiver);
	~UltrasonicWave();
	void initialize();
	void finalize();
	void sense();
	int getState();
};

#endif

