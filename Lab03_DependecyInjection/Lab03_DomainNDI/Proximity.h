// Proximity.h

#ifndef _PROXIMITY_h
#define _PROXIMITY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Sensor.h"
#include "Channel.h"

//#include "wiring_private.h"
//#include "pins_arduino.h"

class Proximity : Sensor
{
public:
	enum EState {
		eReady,
		eRunning,
		eNumStates
	};
	enum EChannelId {
		eIdTransmit,
		eIdReceive,
		eNumChannelIds
	};
private:
	EState eState;
	Channel *pChannels[eNumChannelIds];
	unsigned long distanceInCM;
 public:
	 Proximity(EChannelId eIdTranmit, Channel *pChannelTransmit, EChannelId eIdReceive, Channel *pChannelReceive) {
		 this->pChannels[eIdTranmit] = pChannelTransmit;
		 this->pChannels[eIdReceive] = pChannelReceive;
	 }

	 ~Proximity() {}

	 void initialize() {
		 for (Channel *pChannel : this->pChannels) {
			 pChannel->initialize();
		 }
		 this->eState = EState::eReady;
	 }
	 void finalize() {
		 for (Channel *pChannel : this->pChannels) {
			 pChannel->finalize();
		 }
	 }

	 unsigned long getDistanceInCM() {
		 return distanceInCM;
	 }

	 void start() {
		 if (this->eState == EState::eReady) {
			 this->eState = EState::eRunning;
		 }
	 }

	 //bool wait() {
		// digitalWrite(7, HIGH);
		// delayMicroseconds(10);
		// digitalWrite(7, LOW);

		// distanceInCM = pulseIn(6, HIGH) / 58.2;

		// return true;
	 //}

	 //bool wait() {
		// unsigned long startTime, endTime;

		// if (this->eState == EState::eRunning) {
		//	 this->pChannels[eIdTransmit]->setInput(HIGH);
		//	 this->pChannels[eIdTransmit]->write();
		//	 delayMicroseconds(10);
		//	 this->pChannels[eIdTransmit]->setInput(LOW);
		//	 this->pChannels[eIdTransmit]->write();

		//	 while (true) {
		//		 this->pChannels[eIdReceive]->read();
		//		 if (this->pChannels[eIdReceive]->getOutput() == HIGH ) {
		//			 startTime = millis();
		//			 break;
		//		 }
		//	 }
		//	 while (true) {
		//		 this->pChannels[eIdReceive]->read();
		//		 if (this->pChannels[eIdReceive]->getOutput() == LOW) {
		//			 endTime = millis();
		//			 break;
		//		 }
		//	 }
		//	 distanceInCM = (endTime- startTime);
		//	 
		//	 this->eState = EState::eReady;
		//	 return true;
		// }
		// return false;
	 //}

	 bool wait() {
		  if (this->eState == EState::eRunning) {
			  this->pChannels[eIdTransmit]->setInput(HIGH);
			  this->pChannels[eIdTransmit]->write();
			  delayMicroseconds(10);
			  this->pChannels[eIdTransmit]->setInput(LOW);
			  this->pChannels[eIdTransmit]->write();

			  int pin = this->pChannels[eIdReceive]->getPinNum();
			  uint8_t bit = digitalPinToBitMask(pin);
			  uint8_t port = digitalPinToPort(pin);
			  uint8_t stateMask = bit;
			  unsigned long width = 0;

			  unsigned long numloops = 0;
			  unsigned long maxloops = microsecondsToClockCycles(1000000) / 16;

			  while ((*portInputRegister(port) & bit) == stateMask)
				  if (numloops++ == maxloops)
					  return 0;

			  while ((*portInputRegister(port) & bit) != stateMask)
				  if (numloops++ == maxloops)
					  return 0;

			  while ((*portInputRegister(port) & bit) == stateMask) {
				  if (numloops++ == maxloops)
					  return 0;
				  width++;
			  }

			  distanceInCM = clockCyclesToMicroseconds(width * 21 + 16) / 58.2;

			  this->eState = EState::eReady;
		 	 return true;
		  }
		  return false;
	 }

	 unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout)
	 {
		 // cache the port and bit of the pin in order to speed up the
		 // pulse width measuring loop and achieve finer resolution.  calling
		 // digitalRead() instead yields much coarser resolution.
		 uint8_t bit = digitalPinToBitMask(pin);
		 uint8_t port = digitalPinToPort(pin);
		 uint8_t stateMask = (state ? bit : 0);
		 unsigned long width = 0; // keep initialization out of time critical area

		 // convert the timeout from microseconds to a number of times through
		 // the initial loop; it takes 16 clock cycles per iteration.
		 unsigned long numloops = 0;
		 unsigned long maxloops = microsecondsToClockCycles(timeout) / 16;

		 // wait for any previous pulse to end
		 while ((*portInputRegister(port) & bit) == stateMask)
			 if (numloops++ == maxloops)
				 return 0;

		 // wait for the pulse to start
		 while ((*portInputRegister(port) & bit) != stateMask)
			 if (numloops++ == maxloops)
				 return 0;

		 // wait for the pulse to stop
		 while ((*portInputRegister(port) & bit) == stateMask) {
			 if (numloops++ == maxloops)
				 return 0;
			 width++;
		 }

		 // convert the reading to microseconds. The loop has been determined
		 // to be 20 clock cycles long and have about 16 clocks between the edge
		 // and the start of the loop. There will be some error introduced by
		 // the interrupt handlers.
		 return clockCyclesToMicroseconds(width * 21 + 16);
	 }
};

#endif

