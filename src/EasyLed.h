/*
 EasyLed.h - An LED blinker library for Arduino platform.
 Created by Evert Arias. January 27, 2019.
 EasyLed is provided Copyright © 2019 under MIT License.
*/

#ifndef _EasyLed_h
#define _EasyLed_h

#include "Arduino.h"

#ifdef ESP8266
#define my_min _min
#define my_max _max
#endif
#ifdef ESP32
#define my_min _min
#define my_max _max
#endif

#define MINIMUM_INTERVAL 20
#define COMMON_NEGATIVE 0
#define COMMON_POSITIVE 1

class EasyLed
{
private:
	byte mPin;
	uint8_t mPolarity = COMMON_NEGATIVE;
	byte mBlinks;
	unsigned int mOnDuration;
	unsigned int mOffDuration;
	unsigned int mPauseDuration;
	unsigned int mSequences;
	unsigned long mStartTime;
	unsigned long mLastRunTime;
	void (*mFinishedCallbackFunction)();

public:
	EasyLed(byte const pin);
	EasyLed(byte const pin, uint8_t ledPolarity);
	void setPin(byte const pin);
	void setPolarity(uint8_t polarity);
	void blink(unsigned int const onDuration,
			   unsigned int const offDuration,
			   byte const blinks,
			   unsigned int const pauseDuration,
			   unsigned int const sequences,
			   void (*finishedCallbackFunction)());
	void on();
	void off();
	void onUntil(unsigned int const onDuration, void (*finishedCallbackFunction)());
	void offUntil(unsigned int const offDuration, void (*finishedCallbackFunction)());
	void update();
};

#endif
