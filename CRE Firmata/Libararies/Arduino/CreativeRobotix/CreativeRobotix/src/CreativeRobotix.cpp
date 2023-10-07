/*
 Name:		CreativeRobotix.cpp
 Created:	10/7/2023 4:25:23 PM
 Author:	SEgerton

Creative Science Foundation Creative Robotix Platform Modifications.

Last updated October 7th, 2023

Compile Notes:

Additional libraies required for compile

http://playground.arduino.cc/Code/NewPing

New Ping conflicts with the Tone functions, edit the NewPing.h file
and set the TIMMER_ENABLED setting to 'false'.  The header file can
be found under the 'Arduino/libraries/NewPing' folder.

https://github.com/wayoda/LedControl

*/

#include "CreativeRobotix.h"
#include <arduino.h>

// Wheels, 

#define PIN_LEFT_WHEEL_SERVO	2
#define PIN_RIGHT_WHEEL_SERVO	3

#define VELOCITY_LEFT			0
#define VELOCITY_RIGHT			1

// Arms, head and mouth pin assignments

#define PIN_LEFT_ARM_SERVO		4
#define PIN_RIGHT_ARM_SERVO		5
#define PIN_HEAD_SERVO			6

// Behaviour limits for arms and head

#define ARM_SWING_MAX_DEGREES	50
#define HEAD_SWING_MAX_DEGREES	50

// Speaker

#define SPEAKER					13

#define AUDIO_SAY			0
#define AUDIO_MELODY_BLTIN	1
#define AUDIO_MELODY_USR	2
#define AUDIO_TONE			3
#define AUDIO_MELODY_SPEED	4

#define NOTE_RST 0
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define NOTE_P0	 0000

#define AUDIO_MELODIES_BLTIN	5

const static uint16_t AUDIO_MELODIES_NOTES[] PROGMEM = {
	// Green Sleeves 
	19,
	NOTE_FS3,
	NOTE_A3, NOTE_B3,
	NOTE_CS4, NOTE_D4, NOTE_CS4,
	NOTE_B3, NOTE_GS3,
	NOTE_E3, NOTE_FS3, NOTE_GS3,
	NOTE_A3, NOTE_FS3,
	NOTE_FS3, NOTE_F3, NOTE_FS3,
	NOTE_GS3, NOTE_F3,
	NOTE_CS3,
	// Marry Had a Little Lamb
	26,
	NOTE_E3, NOTE_D3, NOTE_C3, NOTE_D3,
	NOTE_E3, NOTE_E3, NOTE_E3,
	NOTE_D3, NOTE_D3, NOTE_D3,
	NOTE_E3, NOTE_G3, NOTE_G3,
	NOTE_E3, NOTE_D3, NOTE_C3, NOTE_D3,
	NOTE_E3, NOTE_E3, NOTE_E3, NOTE_E3,
	NOTE_D3, NOTE_D3, NOTE_E3, NOTE_D3,
	NOTE_C3,
	// Happy Birthday
	25,
	NOTE_G3, NOTE_G3,
	NOTE_A3, NOTE_G3, NOTE_C4,
	NOTE_B3, NOTE_G3, NOTE_G3,
	NOTE_A3, NOTE_G3, NOTE_D4,
	NOTE_C4, NOTE_G3, NOTE_G3,
	NOTE_G4, NOTE_E4, NOTE_C4,
	NOTE_B3, NOTE_A3, NOTE_G4, NOTE_G4,
	NOTE_E4, NOTE_C4, NOTE_D4,
	NOTE_C4,
	// Star Wars
	40,
	NOTE_A3, NOTE_A3, NOTE_A3,
	NOTE_D4, NOTE_A4, NOTE_RST,
	NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_D5, NOTE_A4,
	NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_D5, NOTE_A4,
	NOTE_G4, NOTE_FS4, NOTE_G4, NOTE_E4, NOTE_RST, NOTE_A3, NOTE_A3, NOTE_A3,
	NOTE_D4, NOTE_A4,
	NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_D5, NOTE_A4,
	NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_D5, NOTE_A4,
	NOTE_G4, NOTE_FS4, NOTE_G4, NOTE_E4,
	// Chariots of Fire
	81,
	NOTE_C4, NOTE_F4, NOTE_G4, NOTE_A4,
	NOTE_G4, NOTE_E4, NOTE_RST, NOTE_C4, NOTE_F4, NOTE_G4, NOTE_A4,
	NOTE_G4, NOTE_RST, NOTE_C4, NOTE_F4, NOTE_G4, NOTE_A4,
	NOTE_G4, NOTE_E4, NOTE_RST, NOTE_E4, NOTE_F4, NOTE_E4, NOTE_C4,
	NOTE_C4, NOTE_RST, NOTE_C4, NOTE_F4, NOTE_G4, NOTE_A4,
	NOTE_G4, NOTE_E4, NOTE_RST, NOTE_C4, NOTE_F4, NOTE_G4, NOTE_A4,
	NOTE_G4, NOTE_RST, NOTE_C4, NOTE_F4, NOTE_G4, NOTE_A4,
	NOTE_G4, NOTE_E4, NOTE_RST, NOTE_E4, NOTE_F4, NOTE_E4, NOTE_C4,
	NOTE_C4, NOTE_RST, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4,
	NOTE_B4, NOTE_G4, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4,
	NOTE_B4, NOTE_RST, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4,
	NOTE_B4, NOTE_G4, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_E4, NOTE_F4, NOTE_E4, NOTE_C4,
	NOTE_C4
};

const uint8_t AUDIO_MELODIES_NOTES_LEN = sizeof(AUDIO_MELODIES_NOTES) / sizeof(uint16_t);

const static uint8_t AUDIO_MELODIES_DURATIONS[] PROGMEM = {
	// Green Sleevs
	19,
	4,
	2, 4,
	3, 8, 4,
	2, 4,
	3, 8, 4,
	2, 4,
	3, 8, 4,
	2, 4,
	1,
	// Mary Had a Little Lamb
	26,
	4, 4, 4, 4,
	4, 4, 2,
	4, 4, 2,
	4, 4, 2,
	4, 4, 4, 4,
	4, 4, 4, 4,
	4, 4, 4, 4,
	1,
	// Happy Birthday
	25,
	8, 8,
	4, 4, 4,
	2, 8, 8,
	4, 4, 4,
	2, 8, 8,
	4, 4, 4,
	4, 4, 8, 8,
	4, 4, 4,
	2,
	// Star Wars
	40,
	12, 12, 12,
	2, 2, 8,
	12, 12, 12, 2, 4,
	12, 12, 12, 2, 4,
	12, 12, 12, 2, 8, 12, 12, 12,
	2, 2,
	12, 12, 12, 2, 4,
	12, 12, 12, 2, 4,
	12, 12, 12, 2,
	// Chariots of fire
	81,
	8, 12, 12, 12,
	4, 4, 8, 8, 12, 12, 12,
	2, 8, 8, 12, 12, 12,
	4, 4, 8, 8, 12, 12, 12,
	2, 8, 8, 12, 12, 12,
	4, 4, 8, 8, 12, 12, 12,
	2, 8, 8, 12, 12, 12,
	4, 4, 8, 8, 12, 12, 12,
	2, 8, 8, 12, 12, 12,
	4, 16, 4, 16, 4, 16, 12, 12, 12,
	2, 8, 8, 12, 12, 12,
	4, 16, 4, 16, 4, 16, 12, 12, 12,
	2
};

const uint8_t AUDIO_MELODIES_DURATIONS_LEN = sizeof(AUDIO_MELODIES_DURATIONS) / sizeof(uint8_t);

const static uint16_t NOTES[] PROGMEM = { // NOTE_P0 included to force a nice hash function 
	NOTE_A1, NOTE_AS1, NOTE_B1, NOTE_P0, NOTE_C1, NOTE_CS1, NOTE_D1, NOTE_DS1, NOTE_E1, NOTE_P0, NOTE_F1, NOTE_FS1, NOTE_G1, NOTE_GS1,	// Scale C1
	NOTE_A2, NOTE_AS1, NOTE_B2, NOTE_P0, NOTE_C2, NOTE_CS2, NOTE_D2, NOTE_DS2, NOTE_E2, NOTE_P0, NOTE_F2, NOTE_FS2, NOTE_G2, NOTE_GS2,	// Scale C2 
	NOTE_A3, NOTE_AS1, NOTE_B3, NOTE_P0, NOTE_C3, NOTE_CS3, NOTE_D3, NOTE_DS3, NOTE_E3, NOTE_P0, NOTE_F3, NOTE_FS3, NOTE_G3, NOTE_GS3,	// Scale C3 
	NOTE_A4, NOTE_AS1, NOTE_B4, NOTE_P0, NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_P0, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4,	// Scale C4 
	NOTE_A5, NOTE_AS1, NOTE_B5, NOTE_P0, NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_P0, NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_GS5,	// Scale C5 
	NOTE_A6, NOTE_AS1, NOTE_B6, NOTE_P0, NOTE_C6, NOTE_CS6, NOTE_D6, NOTE_DS6, NOTE_E6, NOTE_P0, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_GS6,	// Scale C6 
	NOTE_A7, NOTE_AS1, NOTE_B7, NOTE_P0, NOTE_C7, NOTE_CS7, NOTE_D7, NOTE_DS7, NOTE_E7, NOTE_P0, NOTE_F7, NOTE_FS7, NOTE_G7, NOTE_GS7,	// Scale C7 
	NOTE_P0, NOTE_P0, NOTE_P0, NOTE_P0, NOTE_C8, NOTE_CS8, NOTE_D1, NOTE_DS8															// Scale C8 
};

const uint8_t NOTES_LEN = sizeof(NOTES) / sizeof(uint16_t);


// Local 8x8 display data

const static uint32_t LED_DISPLAY_IMAGES[][2] PROGMEM = {
	0x3c420018, 0xe7a5a5e7,			// smile
	0x007e0018, 0xe7a5a5e7,			// neutral
	0x423c0018, 0xe7a5a5e7,			// frown
	0x0c0c000c, 0x1830331e,			// question mark
	0x00005735, 0x35570000,			// OK
	0x00040a11, 0x20408000,			// tick
	0x00422418, 0x18244200,			// cross
	0x7e3c1805, 0x03070507,			// rock
	0x1f3e7cf9, 0xf1070507,			// paper
	0xd8f82027, 0x54570107,			// sissors
	0x10387cfe, 0xfeee4400,			// Heart
	0x060e0c08, 0x08281800,			// Quaver
	0x066eecc8, 0x8898f000,			// Quaver x 2
	0x00000000, 0x00000000			// blank
};

const uint8_t LED_DISPLAY_IMAGES_LEN = sizeof(LED_DISPLAY_IMAGES) / sizeof(uint32_t) / 2;

const static uint32_t LED_DISPLAY_DIGITS[][2] PROGMEM = {
	0x0000e0a0, 0xa0a0e000,			// 0
	0x00008080, 0x80808000,			// 1
	0x0000e020, 0xe080e000,			// 2	
	0x0000e080, 0xe080e000,			// 3
	0x00008080, 0xe0a0a000,			// 4
	0x0000e080, 0xe020e000,			// 5
	0x0000e0a0, 0xe020e000,			// 6
	0x00008080, 0x8080e000,			// 7
	0x0000e0a0, 0xe0a0e000,			// 8
	0x00008080, 0xe0a0e000			// 9
};

const int LED_DIGITS_LEN = sizeof(LED_DISPLAY_DIGITS) / sizeof(uint32_t) / 2;

const static uint32_t LED_DISPLAY_CHARACTERS[][2] PROGMEM = {
	0x00000000, 0x00000000,
	0x18001818, 0x3c3c1800,
	0x00000000, 0x286c6c00,
	0x6c6cfe6c, 0xfe6c6c00,
	0x103c4038, 0x04781000,
	0x60660c18, 0x30660600,
	0xfc66a614, 0x3c663c00,
	0x00000000, 0x00040400,
	0x60301818, 0x18306000,
	0x060c1818, 0x180c0600,
	0x006c38fe, 0x386c0000,
	0x0010107c, 0x10100000,
	0x00000000, 0x60303000,
	0x0000003c, 0x00000000,
	0x06060000, 0x00000000,
	0x00060c18, 0x30600000,
	0x3c66666e, 0x76663c00,
	0x7e181818, 0x1c181800,
	0x7e060c30, 0x60663c00,
	0x3c666038, 0x60663c00,
	0x30307e32, 0x34383000,
	0x3c666060, 0x3e067e00,
	0x3c66663e, 0x06663c00,
	0x18181830, 0x30667e00,
	0x3c66663c, 0x66663c00,
	0x3c66607c, 0x66663c00,
	0x00181800, 0x18180000,
	0x0c181800, 0x18180000,
	0x6030180c, 0x18306000,
	0x00003c00, 0x3c000000,
	0x060c1830, 0x180c0600,
	0x18001838, 0x60663c00,
	0x003c421a, 0x3a221c00,
	0x6666667e, 0x66663c00,			// A
	0x3e66663e, 0x66663e00,			// B
	0x3c660606, 0x06663c00,			// C
	0x3e666666, 0x66663e00,			// D
	0x7e06063e, 0x06067e00,			// E
	0x0606063e, 0x06067e00,			// F
	0x3c667606, 0x06663c00,			// G
	0x6666667e, 0x66666600,			// H
	0x3c181818, 0x18183c00,			// ...
	0x1c363630, 0x30307800,
	0x66361e0e, 0x1e366600,
	0x7e060606, 0x06060600,
	0xc6c6c6d6, 0xfeeec600,
	0xc6c6e6f6, 0xdecec600,
	0x3c666666, 0x66663c00,
	0x06063e66, 0x66663e00,
	0x603c7666, 0x66663c00,
	0x66361e3e, 0x66663e00,
	0x3c66603c, 0x06663c00,
	0x18181818, 0x185a7e00,
	0x7c666666, 0x66666600,			// ...
	0x183c6666, 0x66666600,			// V
	0xc6eefed6, 0xc6c6c600,			// W
	0xc6c66c38, 0x6cc6c600,			// X
	0x1818183c, 0x66666600,			// Y
	0x7e060c18, 0x30607e00,			// Z
	0x78181818, 0x18187800,			// [
	0x00603018, 0x0c060000,			// '\'
	0x1e181818, 0x18181e00,			// ]
	0x00000082, 0x44281000,			// ^
	0x7e000000, 0x00000000,			// _
	0x0000000c, 0x18181800,			// `
	0x7c667c60, 0x3c000000,			// a
	0x3e66663e, 0x06060600,			// b
	0x3c660666, 0x3c000000,			// c
	0x7c66667c, 0x60606000,			// ...
	0x3c067e66, 0x3c000000,
	0x0c0c3e0c, 0x0c6c3800,
	0x3c607c66, 0x667c0000,
	0x6666663e, 0x06060600,
	0x3c181818, 0x00180000,
	0x1c363630, 0x30003000,
	0x66361e36, 0x66060600,
	0x18181818, 0x18181800,
	0xd6d6feee, 0xc6000000,
	0x6666667e, 0x3e000000,
	0x3c666666, 0x3c000000,
	0x06063e66, 0x663e0000,
	0xf0b03c36, 0x363c0000,
	0x06066666, 0x3e000000,
	0x3e403c02, 0x7c000000,
	0x1818187e, 0x18180000,
	0x7c666666, 0x66000000,			// ...
	0x183c6666, 0x00000000,			// v
	0x7cd6d6d6, 0xc6000000,			// w
	0x663c183c, 0x66000000,			// x
	0x3c607c66, 0x66000000,			// y
	0x3c0c1830, 0x3c000000,			// z
	0x7018180c, 0x18187000,
	0x0e181830, 0x18180e00,
	0x00080808, 0x08080000,
	0x00000036, 0x5c000000,
	0x00000000, 0x00000000			// del
};

const int LED_DISPLAY_CHARACTERS_LEN = sizeof(LED_DISPLAY_CHARACTERS) / sizeof(uint32_t) / 2;

#define GETSCROLLROW(c, b)				((byte)((c >> (8*b)) & 0xFF))
#define GETDISPLAYROW(c, b)				((byte)((c >> (8*(7-b)) & 0xFF)))

#define LED_DISPLAY_SMILE				0
#define LED_DISPLAY_NEUTRAL				1
#define LED_DISPLAY_FROWN				2	
#define LED_DISPLAY_QUESTION			3
#define LED_DISPLAY_OK					4
#define LED_DISPLAY_TICK				5	
#define LED_DISPLAY_CROSS				6	
#define LED_DISPLAY_ROCK				7
#define LED_DISPLAY_PAPER				8
#define LED_DISPLAY_SISSORS				9	
#define LED_DISPLAY_QUAVER				10
#define LED_DISPLAY_QUAVERx2			11
#define LED_DISPLAY_HEART				12
#define LED_DISPLAY_BLANK				13 

#define LED_SET_IMAGE					1
#define LED_SET_SCROLL_TEXT				2
#define LED_SET_NUMBER					3
#define LED_SET_ROW_DATA				4
#define LED_SET_SET_PIXEL				5
#define LED_SET_CLEAR					6

#define LED_DISPLAY_TYPE_IMAGES			0
#define LED_DISPLAY_TYPE_DIGITS			1
#define LED_DISPLAY_TYPE_ASCII			2


CreativeRobotix::CreativeRobotix() {

	// Initialise the MAX72XX display 

	_ledDisplay.shutdown(0, false);		// The MAX72XX is in power-saving mode on startup
	_ledDisplay.setIntensity(0, 7);		// Set the brightness to (7), maximum value (15)
	_ledDisplay.clearDisplay(0);		// and clear the display
}

void CreativeRobotix::begin(void) {
	// LED Display to neutral

	setLEDDisplayImage(LED_DISPLAY_NEUTRAL);

	// Say hello, I'm active
	sayDirect("Hello World!");

	setLEDDisplayImage(LED_DISPLAY_SMILE);
}

void CreativeRobotix::restoreLEDDisplay(void){
	switch (_ledDisplayType) {
	case LED_DISPLAY_TYPE_IMAGES:
		setLEDDisplayImage(_ledDisplayImage);
		break;
	case LED_DISPLAY_TYPE_DIGITS:
		setLEDDisplayDigits(_ledDisplayDigits);
		break;
	case LED_DISPLAY_TYPE_ASCII:
		setLEDDisplayASCII(_ledDisplayASCII);
		break;
	default:
		break;
	}
}

void CreativeRobotix::setLEDDisplayImage(uint8_t image) {
	uint64_t character;
	character = pgm_read_dword(&(LED_DISPLAY_IMAGES[image][0])); // High
	character = (character << 32) | pgm_read_dword(&(LED_DISPLAY_IMAGES[image][1])); // Low
	setLEDisplay(character);
	ledDisplayImage = image;
	ledDisplayType = LED_DISPLAY_TYPE_IMAGES;
}


void CreativeRobotix::setLEDDisplayDigits(uint8_t number) {
	uint64_t digit_tens, digit_units;
	digit_tens = pgm_read_dword(&(LED_DISPLAY_DIGITS[int(number / 10)][0])); // High
	digit_tens = (digit_tens << 32) | pgm_read_dword(&(LED_DISPLAY_DIGITS[int(number / 10)][1])); // Low
	digit_units = pgm_read_dword(&(LED_DISPLAY_DIGITS[number - (int(number / 10) * 10)][0])); // High
	digit_units = (digit_units << 32) | pgm_read_dword(&(LED_DISPLAY_DIGITS[number - (int(number / 10) * 10)][1])); // Low
	setLEDisplay((digit_tens >> 4) | digit_units);
	ledDisplayDigits = number;
	ledDisplayType = LED_DISPLAY_TYPE_DIGITS;
}


void CreativeRobotix::setLEDDisplayASCII(uint8_t ascii) {
	uint64_t character;
	character = pgm_read_dword(&(LED_DISPLAY_IMAGES[ascii][0])); // High
	character = (character << 32) | pgm_read_dword(&(LED_DISPLAY_CHARACTERS[ascii][1])); // Low
	setLEDisplay(character);
	ledDisplayASCII = ascii;
	ledDisplayType = LED_DISPLAY_TYPE_ASCII;
}

void CreativeRobotix::setLEDisplay(const uint64_t character)
{
	for (uint8_t row = 0; row < 8; row++)
	{
		ledDisplay.setRow(0, row, GETDISPLAYROW(character, row));
	}
}