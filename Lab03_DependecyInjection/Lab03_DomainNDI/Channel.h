// Channel.h

#ifndef _CHANNEL_h
#define _CHANNEL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Channel
{
public:
	enum eChannelType {
		eAnalog,
		eDigital,
		ePWM,
		eNumTypes
	};
	enum eChannelIOType {
		eInput,
		eOutput,
		eNumIOTypes
	};
private:
	eChannelType pinType_;
	eChannelIOType pinIOType_;
	int pinNum_;
	int input_;
	int output_;

public:
	Channel(eChannelType pinType, eChannelIOType pinIOType, int pinNum) :
		pinType_(pinType), pinIOType_(pinIOType), pinNum_(pinNum) {}

	~Channel() {}

	void initialize() {
		this->input_ = 0;
		this->output_ = 0;

		if (this->pinIOType_ == eInput) {
			pinMode(this->pinNum_, INPUT);
		}
		else if (this->pinIOType_ == eOutput) {
			pinMode(this->pinNum_, OUTPUT);
		}
	}

	void finalize() {}

	void setInput(int input) {
		this->input_ = input;
	}

	int getPinNum() {
		return pinNum_;
	}

	int getOutput() {
		return this->output_;
	}

	bool read() {
		switch (this->pinType_)
		{
		case eAnalog:	this->output_ = analogRead(this->pinNum_); return true;
		case eDigital:	this->output_ = digitalRead(this->pinNum_); return true;
		case ePWM:		this->output_ = analogRead(this->pinNum_); return true;
		default: return false;
		}
	}

	bool write() {
		switch (this->pinType_)
		{
		case eAnalog:	analogWrite(this->pinNum_, this->input_); return true;
		case eDigital:	digitalWrite(this->pinNum_, this->input_); return true;
		case ePWM:		analogWrite(this->pinNum_, this->input_); return true;
		default: return false;
		}
	}
};

#endif

