// 
// 
// 

#include "LEDManager.h"

LEDManager::LEDManager() :
	illuminantChannel(0),

	ultrasonicWaveChannelTransmitter(7),
	ultrasonicWaveChannelReceiver(6),

	rgbLEDchannelRed(3),
	rgbLEDchannelGreen(10),
	rgbLEDchannelBlue(5),

	illuminant(Illuminant::EChannelId::eIdCDS, &illuminantChannel),

	ultrasonicWave(UltrasonicWave::EChannelId::eIdTransmitter, &ultrasonicWaveChannelTransmitter,
				   UltrasonicWave::EChannelId::eIdReceiver, &ultrasonicWaveChannelReceiver),

	rgbLED(RGBLED::EChannelId::eIdRed, &rgbLEDchannelRed,
		RGBLED::EChannelId::eIdGreen, &rgbLEDchannelGreen,
		RGBLED::EChannelId::eIdBlue, &rgbLEDchannelBlue)
{}

LEDManager::~LEDManager() {}

void LEDManager::initialize() {
	this->illuminant.initialize();
	this->ultrasonicWave.initialize();
	this->rgbLED.initialize();

	this->illuminant.start();
	this->ultrasonicWave.start();
	this->rgbLED.start();
}

void LEDManager::finalize() {
	this->illuminant.finalize();
	this->ultrasonicWave.finalize();
	this->rgbLED.finalize();
}

void LEDManager::process() {
	int lightFactor = illuminant.getCDSLight() > 800 ? 1 : 3;
	int distance = ultrasonicWave.getElapsedTime() / 58.2;

	if (distance < 3) {
		rgbLED.setRGBValue(0, 0, 0);
	}
	else if (distance < 8) {
		rgbLED.setRGBValue(255/lightFactor, 0, 0);
	}
	else if (distance < 12) {
		rgbLED.setRGBValue(0, 255/lightFactor, 0);
	}
	else if (distance < 16) {
		rgbLED.setRGBValue(0, 0, 255/lightFactor);
	}
	else {
		rgbLED.setRGBValue(0, 0, 0);
	}
}

void LEDManager::actuate() {
	if (this->rgbLED.wait()) {
		this->rgbLED.start();
	}
}

void LEDManager::run() {
	if (this->illuminant.wait()) {
		this->illuminant.start();
	}

	if (this->ultrasonicWave.wait()) {
		this->ultrasonicWave.start();
	}

	this->process();
	this->actuate();
}
