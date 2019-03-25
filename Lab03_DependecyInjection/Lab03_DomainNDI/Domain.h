// Domain.h

#ifndef _DOMAIN_h
#define _DOMAIN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Channel.h"
#include "Illuminant.h"
#include "Proximity.h"
#include "RGBLED.h"

class Domain {
private:
	Channel illuminatChannel;

	Channel proximityChannelTransmit;
	Channel proximityChannelReceive;

	Channel rgbLEDchannelRed;
	Channel rgbLEDchannelGreen;
	Channel rgbLEDchannelBlue;

	Illuminant illuminant;
	Proximity proximity;

	RGBLED rgbLED;
	int rValue;
	int gValue;
	int bValue;

public:
	// constructors & destructors
	Domain() :
		illuminatChannel(Channel::eChannelType::eAnalog, Channel::eChannelIOType::eInput, 0),

		proximityChannelTransmit(Channel::eChannelType::eDigital, Channel::eChannelIOType::eOutput, 7),
		proximityChannelReceive(Channel::eChannelType::eDigital, Channel::eChannelIOType::eInput, 6),
	
		rgbLEDchannelRed(Channel::eChannelType::ePWM, Channel::eChannelIOType::eOutput, 3),
		rgbLEDchannelGreen(Channel::eChannelType::ePWM, Channel::eChannelIOType::eOutput, 10),
		rgbLEDchannelBlue(Channel::eChannelType::ePWM, Channel::eChannelIOType::eOutput, 5),

		illuminant(Illuminant::EChannelId::eIdCDS, &illuminatChannel),

		proximity(Proximity::EChannelId::eIdTransmit, &proximityChannelTransmit,
				  Proximity::EChannelId::eIdReceive, &proximityChannelReceive),

		rgbLED(RGBLED::EChannelId::eIdRed, &rgbLEDchannelRed,
			   RGBLED::EChannelId::eIdGreen, &rgbLEDchannelGreen,
			   RGBLED::EChannelId::eIdBlue, &rgbLEDchannelBlue)
	{}
	
	~Domain() {}
	
	void initialize() {
		this->illuminant.start();
		this->proximity.start();
		this->rgbLED.start();
	}
	
	void finalize() {}

	// methods
	void process() {
		int light = illuminatChannel.getOutput();
		Serial.print("   Light: ");
		Serial.print(light);

		if (light < 800) {
			rgbLEDchannelRed.setInput(255);
			rgbLEDchannelGreen.setInput(255);
			rgbLEDchannelBlue.setInput(255);
		}
		else {
			rgbLEDchannelRed.setInput(0);
			rgbLEDchannelGreen.setInput(0);
			rgbLEDchannelBlue.setInput(0);
		}

		unsigned long distance = proximity.getDistanceInCM();
		Serial.print("   Distance: ");
		Serial.print(distance);
	}

	void actuate() {
		if (this->rgbLED.wait()) {
			this->rgbLED.start();
		}
	}

	void run() {
		if (this->illuminant.wait()) {
			this->illuminant.start();
		}
		if (this->proximity.wait()) {
			this->proximity.start();
		}
		this->process();
		this->actuate();
	}
};

#endif

