// AutoDoorWithLighting.h

#ifndef _AUTODOORWITHLIGHTING_h
#define _AUTODOORWITHLIGHTING_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "Domain.h"
#include "AnalogInputChannel.h"
#include "DigitalInputChannel.h"
#include "DigitalOutputChannel.h"
#include "PWMOutputChannel.h"
#include "Illuminant.h"
#include "UltrasonicWaveTransmitter.h"
#include "UltrasonicWaveReceiver.h"
#include "RGBLED.h"
#include "ServoMotor.h"

class AutoDoorWithLighting : public Domain
{
private:
	AnalogInputChannel illuminantChannel;

	DigitalOutputChannel proximityChannelTransmit;
	DigitalInputChannel proximityChannelReceive;

	PWMOutputChannel rgbLEDchannelRed;
	PWMOutputChannel rgbLEDchannelGreen;
	PWMOutputChannel rgbLEDchannelBlue;

	PWMOutputChannel servoMotorChannel;

	Illuminant illuminant;

	UltrasonicWaveTransmitter ultrasonicWaveTransmitter;
	UltrasonicWaveReceiver ultrasonicWaveReceiver;

	RGBLED rgbLED;

	ServoMotor servoMotor;

public:
	AutoDoorWithLighting() :
		illuminantChannel(0),

		proximityChannelTransmit(7),
		proximityChannelReceive(6),

		rgbLEDchannelRed(3),
		rgbLEDchannelGreen(10),
		rgbLEDchannelBlue(5),

		servoMotorChannel(9),

		illuminant(Illuminant::EChannelId::eIdCDS, &illuminantChannel),

		ultrasonicWaveTransmitter(UltrasonicWaveTransmitter::EChannelId::eIdTransmit, &proximityChannelTransmit),
		ultrasonicWaveReceiver(UltrasonicWaveReceiver::EChannelId::eIdReceive, &proximityChannelReceive),

		rgbLED(RGBLED::EChannelId::eIdRed, &rgbLEDchannelRed,
			RGBLED::EChannelId::eIdGreen, &rgbLEDchannelGreen,
			RGBLED::EChannelId::eIdBlue, &rgbLEDchannelBlue),

		servoMotor(ServoMotor::EChannelId::eIdAttach, &servoMotorChannel)
	{}

	~AutoDoorWithLighting() {}

	void initialize() {
		this->illuminant.initialize();
		this->ultrasonicWaveTransmitter.initialize();
		this->ultrasonicWaveReceiver.initialize();
		this->rgbLED.initialize();
		this->servoMotor.initialize();

		this->illuminant.start();
		this->ultrasonicWaveTransmitter.start();
		this->ultrasonicWaveReceiver.start();
		this->rgbLED.start();
		this->servoMotor.start();
	}

	void finalize() {
		this->illuminant.finalize();
		this->ultrasonicWaveTransmitter.finalize();
		this->ultrasonicWaveReceiver.finalize();
		this->rgbLED.finalize();
		this->servoMotor.finalize();
	}

	void process() {
		int lightFactor = illuminantChannel.getData() > 800 ? 1 : 3;
		int distance = ultrasonicWaveReceiver.getElapsedTime() / 58.2;

		if (distance < 3) {
			rgbLEDchannelRed.setData(0);
			rgbLEDchannelGreen.setData(0);
			rgbLEDchannelBlue.setData(0);
		}
		else if (distance < 8) {
			rgbLEDchannelRed.setData(255 / lightFactor);
			rgbLEDchannelGreen.setData(0);
			rgbLEDchannelBlue.setData(0);
			servoMotorChannel.setData(90);
		}
		else if (distance < 12) {
			rgbLEDchannelRed.setData(0);
			rgbLEDchannelGreen.setData(255 / lightFactor);
			rgbLEDchannelBlue.setData(0);
		}
		else if (distance < 16) {
			rgbLEDchannelRed.setData(0);
			rgbLEDchannelGreen.setData(0);
			rgbLEDchannelBlue.setData(255 / lightFactor);
		}
		else {
			rgbLEDchannelRed.setData(0);
			rgbLEDchannelGreen.setData(0);
			rgbLEDchannelBlue.setData(0);
		}
	}

	void actuate() {
		if (this->rgbLED.wait()) {
			this->rgbLED.start();
		}
		//if (this->servoMotor.wait()) {
		//	this->servoMotor.start();
		//}
	}

	void run() {
		if (this->illuminant.wait()) {
			this->illuminant.start();
		}

		if (this->ultrasonicWaveTransmitter.wait()) {
			this->ultrasonicWaveTransmitter.start();
		}

		if (this->ultrasonicWaveReceiver.wait()) {
			this->ultrasonicWaveReceiver.start();
		}

		this->process();
		this->actuate();
	}
};

#endif

