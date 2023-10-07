/*
 Name:		CreativeRobotix.h
 Created:	10/7/2023 4:25:23 PM
 Author:	SEgerton
 Editor:	http://www.visualmicro.com
*/

#ifndef _CreativeRobotix_h
#define _CreativeRobotix_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
	#include <NewPing.h>	
	#include <LedControl.h>
#else
	#include "WProgram.h"
#endif

// MAX72XX LED 8x8 display

#define MAX72XX_HEIGHT			8
#define MAX72XX_WIDTH			8
#define MAX72XX_DIN				9
#define MAX72XX_CS				8
#define MAX72XX_CLK				7

// Ultrasound Sensor

#define HCSR04_TRIGGER			11
#define HCSR04_ECHO				10
#define HCSR04_MAX_DISTANCE		60 // Sensor returns a range between 1 to HCR04_MAX_DISTANCE, and 0 otherwise
#define HCSR04_CLEAR			0

// Bluetooth

#define PIN_SETUP_HC06			21

#define HC06_DATA_BUFFER_LEN	10

#define HC06_CMD_SETNAME		1
#define HC06_CMD_SETPIN			2

// Data buffers for aound and text

#define MELODY_TO_PLAY_BUFFER_LEN	30

#define TEXT_TO_SAY_BUFFER_LEN		40

#define TEXT_TO_SCROLL_BUFFER_LEN	40

// Class defination

class CreativeRobotix
{
public:
	CreativeRobotix();
	void begin();

private:
	LedControl _ledDisplay = LedControl(MAX72XX_DIN, MAX72XX_CLK, MAX72XX_CS, 0);
	NewPing _sonar(HCSR04_TRIGGER, HCSR04_ECHO, HCSR04_MAX_DISTANCE); // NewPing setup of pins and maximum distance.

	boolean _isArmsSwing = false;
	boolean _isHeadSwing = false;
	boolean _isTextToScroll = false;
	boolean _isTextToSay = false;
	boolean _isMelodyToPlay = false;

	boolean _isUserMelody = false;

	uint8_t _ledDisplayImage = 0, _ledDisplayDigits = 0, _ledDisplayASCII = 0;

	uint8_t _ledDisplayType = 0;

	uint8_t _armSwingSpeed = 0, _headSwingSpeed = 0;

	uint8_t _textToScrollLen = 0;
	byte _textToScrollBuffer[TEXT_TO_SCROLL_BUFFER_LEN];

	float _melodyToPlaySpeed = 1.0;
	uint8_t	_melodyToPlayLen = 0, _melodyRecordStart = 0;
	uint16_t _melodyToPlayNoteBuffer[MELODY_TO_PLAY_BUFFER_LEN];
	uint8_t _melodyToPlayDurationBuffer[MELODY_TO_PLAY_BUFFER_LEN];

	unsigned long _scrollInterval = 200;
	unsigned long _armSwingInterval = 25;
	unsigned long _headSwingInterval = 50;

	uint8_t _textToSayLen = 0;
	byte _textToSayBuffer[TEXT_TO_SAY_BUFFER_LEN];

	uint8_t _hc06DataBuffer[HC06_DATA_BUFFER_LEN];

	void restoreLEDDisplay();
};

#endif



