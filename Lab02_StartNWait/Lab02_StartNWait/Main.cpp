// 
// 
// 

#include "Main.h"

#define _USE_MIMIC_THREAD							false

// 조도 센서
#define _ANALOG_PIN_NUM_FOR_ILLUMINANT				0

// 초음파 거리 센서
#define _DIGITAL_IN_PIN_NUM_FOR_PROXIMITY			6
#define _DIGITAL_OUT_PIN_NUM_FOR_PROXIMITY			7
#define _RETENTION_TIME_FOR_FIRING_WAVE_IN_MS		10

// LCD
#define _DIGITAL_OUT_PIN_NUM_FOR_LCD_RS				12
#define _DIGITAL_OUT_PIN_NUM_FOR_LCD_ENABLE			11
#define _DIGITAL_OUT_PIN_NUM_FOR_LCD_D4				2
#define _DIGITAL_OUT_PIN_NUM_FOR_LCD_D5				3
#define _DIGITAL_OUT_PIN_NUM_FOR_LCD_D6				4
#define _DIGITAL_OUT_PIN_NUM_FOR_LCD_D7				5
#define _NUM_ROWS_OF_LCD							2
#define _NUM_COLS_OF_LCD							16

// RGBLED
#define _DIGITAL_OUT_PIN_NUM_FOR_RGBLED_R			13
#define _DIGITAL_OUT_PIN_NUM_FOR_RGBLED_G			10
#define _DIGITAL_OUT_PIN_NUM_FOR_RGBLED_B			1

// ServoMotor
#define _DIGITAL_OUT_PIN_NUM_FOR_SERVO_MOTOR		9

// PiezoSpeaker
#define _DIGITAL_OUT_PIN_NUM_FOR_PIEZO_SPEAKER		8
#define _INTERVAL_BT_NOTES							400

unsigned long prevMTIlluminant = 0;
unsigned long prevMTProximity = 0;
unsigned long prevMTLCD = 0;
unsigned long prevMTRGBLED = 0;
unsigned long prevMTServoMotor = 0;
unsigned long prevMTPiezoSpeaker = 0;

unsigned long intervalIlluminant = 10;
unsigned long intervalProximity = 10;
unsigned long intervalLCD = 1000;
unsigned long intervalRGBLED = 10;
unsigned long intervalServoMotor = 100;
unsigned long intervalPiezoSpeaker = _INTERVAL_BT_NOTES;

#define _MASK_ILLUMINANT	0x01
#define _MASK_PROXIMITY		0x02
unsigned char flag = 0x00;

int cdsLightVauleForDayNNight =	800;
int shortDistance = 5;
int middleDistance = 10;
int longDistance = 15;
int maxAngleOfServoMotor = 180;

int QUEUE_DistanceInCM;
int QUEUE_CDSLight;
String QUEUE_StringOne;
String QUEUE_StringTwo;

Main::Main() :
	illuminant(Illuminant(_ANALOG_PIN_NUM_FOR_ILLUMINANT)),
	proximity(Proximity(_DIGITAL_IN_PIN_NUM_FOR_PROXIMITY,
		_DIGITAL_OUT_PIN_NUM_FOR_PROXIMITY,
		_RETENTION_TIME_FOR_FIRING_WAVE_IN_MS)),
	lcd(LCD(_DIGITAL_OUT_PIN_NUM_FOR_LCD_RS,
		_DIGITAL_OUT_PIN_NUM_FOR_LCD_ENABLE,
		_DIGITAL_OUT_PIN_NUM_FOR_LCD_D4,
		_DIGITAL_OUT_PIN_NUM_FOR_LCD_D5,
		_DIGITAL_OUT_PIN_NUM_FOR_LCD_D6,
		_DIGITAL_OUT_PIN_NUM_FOR_LCD_D7,
		_NUM_ROWS_OF_LCD,
		_NUM_COLS_OF_LCD)),
	rgbLED(RGBLED(_DIGITAL_OUT_PIN_NUM_FOR_RGBLED_R,
		_DIGITAL_OUT_PIN_NUM_FOR_RGBLED_G,
		_DIGITAL_OUT_PIN_NUM_FOR_RGBLED_B)),
	servoMotor(ServoMotor(_DIGITAL_OUT_PIN_NUM_FOR_SERVO_MOTOR)),
	piezoSpeaker(PiezoSpeaker(_DIGITAL_OUT_PIN_NUM_FOR_PIEZO_SPEAKER,
		_INTERVAL_BT_NOTES))
{
	arrDevice[0] = &illuminant;
	arrDevice[1] = &proximity;
	arrDevice[2] = &lcd;
	arrDevice[3] = &rgbLED;
	arrDevice[4] = &servoMotor;
	arrDevice[5] = &piezoSpeaker;
}

void Main::init()
{
	for (int i = 0; i < MAX_NUM_DEVICES; i++)
	{
		arrDevice[i]->init();
	}

	for (int i = 0; i < MAX_NUM_DEVICES; i++)
	{
		arrDevice[i]->start();
	}
}

void Main::run()
{
	unsigned long prevMT = 0;
	unsigned long curMT = 0;
	unsigned long diff = 0;

	while (true)
	{
		prevMT = curMT;
		curMT = millis();
		diff = curMT - prevMT;
		Serial.print("current millis: ");
		Serial.print(curMT);
		Serial.print("    diff: ");
		Serial.print(diff);
		if (diff < 25) Serial.println("     *");
		else if (diff < 100) Serial.println("     ***");
		else if (diff < 300) Serial.println("     *****");
		else if (diff < 1000) Serial.println("     ********");
		else Serial.println("     ****************");

		if (illuminant.wait())
		{
			flag |= _MASK_ILLUMINANT;
		}
		else
		{
			flag &= ~_MASK_ILLUMINANT;
		}

		if (proximity.wait())
		{
			flag |= _MASK_PROXIMITY;
		}
		else
		{
			flag &= ~_MASK_PROXIMITY;
		}

		if (curMT - prevMTLCD > intervalLCD)
		{
			if (flag & 3)
//			if ((flag & _MASK_ILLUMINANT) || (flag & _MASK_PROXIMITY))
			{
				if (lcd.wait())
				{
					prevMTLCD = curMT;
				}
			}
		}

		if (curMT - prevMTRGBLED > intervalRGBLED)
		{
			if (flag & _MASK_ILLUMINANT)
			{
				if (rgbLED.wait())
				{
					prevMTRGBLED = curMT;
				}
			}
		}

		if (curMT - prevMTServoMotor > intervalServoMotor)
		{
			if (flag & _MASK_PROXIMITY)
			{
				if (_USE_MIMIC_THREAD ? servoMotor.slicedWait() : servoMotor.wait())
				{
					prevMTServoMotor = curMT;
				}
			}
		}

		if (curMT - prevMTPiezoSpeaker > intervalPiezoSpeaker)
		{
			if (flag & _MASK_PROXIMITY)
			{
				if (_USE_MIMIC_THREAD ? piezoSpeaker.slicedWait() : piezoSpeaker.wait())
				{
					prevMTPiezoSpeaker = curMT;
				}
			}
		}
	}
}


