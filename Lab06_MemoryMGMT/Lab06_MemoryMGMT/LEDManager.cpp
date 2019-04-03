// 
// 
// 

#include "LEDManager.h"
#include "Globals.h"

LEDManager::LEDManager() :
	illuminantChannel(MJUC_CHANNEL_ILLUMINANT),

	ultrasonicWaveChannelTransmitter(MJUC_CHANNEL_ULTRASONIC_WAVE_TRANSMITTER),
	ultrasonicWaveChannelReceiver(MJUC_CHANNEL_ULTRASONIC_WAVE_RECEIVER),

	rgbLEDchannelRed(MJUC_CHANNEL_RGBLED_RED),
	rgbLEDchannelGreen(MJUC_CHANNEL_RGBLED_GREEN),
	rgbLEDchannelBlue(MJUC_CHANNEL_RGBLED_BLUE),

	illuminant(Illuminant::EChannelId::eIdCDS, &illuminantChannel),

	ultrasonicWave(UltrasonicWave::EChannelId::eIdTransmitter, &ultrasonicWaveChannelTransmitter,
		UltrasonicWave::EChannelId::eIdReceiver, &ultrasonicWaveChannelReceiver),

	rgbLED(RGBLED::EChannelId::eIdRed, &rgbLEDchannelRed,
		RGBLED::EChannelId::eIdGreen, &rgbLEDchannelGreen,
		RGBLED::EChannelId::eIdBlue, &rgbLEDchannelBlue),
	arrSensor{ &illuminant,&ultrasonicWave },
	arrActuator{ &rgbLED }
{}

LEDManager::~LEDManager() {}

void LEDManager::initialize() {
	for (Sensor* pSensor : this->arrSensor) {
		pSensor->initialize();
	}
	for (Actuator* pActuator : this->arrActuator) {
		pActuator->initialize();
	}

	this->eState = EState::eReady;
}

void LEDManager::finalize() {
	for (Sensor* pSensor : this->arrSensor) {
		pSensor->finalize();
	}
	for (Actuator* pActuator : this->arrActuator) {
		pActuator->finalize();
	}
}

void LEDManager::run() {
	if (wait()) {
		start();
	}
}

void LEDManager::start() {
	if (this->eState == EState::eRunning) {
		this->sense();
		this->process();
		this->actuate();
		this->eState = EState::eReady;
	}
}

bool LEDManager::wait() {
	if (this->eState == EState::eReady) {
		this->eState = EState::eRunning;
		return true;
	}
	return false;
}

void LEDManager::sense() {
	for (Sensor* pSensor : this->arrSensor) {
		pSensor->sense();
	}
}

void LEDManager::process() {
	int lightState = illuminant.getState();
	int distanceState = ultrasonicWave.getState();

	rgbLED.setState(lightState, distanceState);
}

void LEDManager::actuate() {
	for (Actuator* pActuator : this->arrActuator) {
		pActuator->actuate();
	}
}