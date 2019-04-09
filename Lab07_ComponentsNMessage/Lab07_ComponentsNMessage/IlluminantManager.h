// IlluminantManager.h

#ifndef _ILLUMINANTMANAGER_h
#define _ILLUMINANTMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Component.h"
#include "AnalogInputChannel.h"

class IlluminantManager: public Component
{
public:
	enum EState {
		eReady,
		eRunning,
		eNumStates
	};
private:
	EState eState_;
	AnalogInputChannel illuminantChannel_;
	Illuminant illuminant_;
	Component* pTargetComponent_;

public:
	IlluminantManager(Component* pTargetComponent);
	~IlluminantManager();
	void initialize();
	void finalize();
	void generateMessage();
	void processMessage(Message* pMessage);
};

#endif

