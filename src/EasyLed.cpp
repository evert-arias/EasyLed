/*
 EasyLed.h - An LED blinker library for Arduino platform.
 Created by Evert Arias. January 27, 2019.
 EasyLed is provided Copyright © 2019 under MIT License.
*/

#include "Arduino.h"
#include "EasyLed.h"

/* EasyLed */

EasyLed::EasyLed(byte const pin) : mPin(pin), mStartTime(0)
{
  mPolarity = COMMON_NEGATIVE;
  pinMode(pin, OUTPUT);
  if (mPolarity == COMMON_NEGATIVE)
  {
    digitalWrite(pin, LOW);
  }
  else if (mPolarity == COMMON_POSITIVE)
  {
    digitalWrite(pin, HIGH);
  }
}

EasyLed::EasyLed(byte const pin, uint8_t polarity) : mPin(pin), mPolarity(polarity), mStartTime(0)
{
  pinMode(pin, OUTPUT);
  if (mPolarity == COMMON_NEGATIVE)
  {
    digitalWrite(pin, LOW);
  }
  else if (mPolarity == COMMON_POSITIVE)
  {
    digitalWrite(pin, HIGH);
  }
}

void EasyLed::setPin(byte const pin)
{
  mPin = pin;
  pinMode(pin, OUTPUT);
  if (mPolarity == COMMON_NEGATIVE)
  {
    digitalWrite(pin, LOW);
  }
  else if (mPolarity == COMMON_POSITIVE)
  {
    digitalWrite(pin, HIGH);
  }
  mStartTime = 0;
}

void EasyLed::setPolarity(uint8_t polarity)
{
  mPolarity = polarity;
  if (mPolarity == COMMON_NEGATIVE)
  {
    digitalWrite(mPin, LOW);
  }
  else if (mPolarity == COMMON_POSITIVE)
  {
    digitalWrite(mPin, HIGH);
  }
}

void EasyLed::blink(unsigned int const onDuration,
                       unsigned int const offDuration,
                       byte const blinks,
                       unsigned int const pauseDuration,
                       unsigned int const sequences,
                       void (*finishedCallbackFunction)())
{
  mOnDuration = onDuration ? max(MINIMUM_INTERVAL, onDuration) : 0;
  mOffDuration = offDuration ? max(MINIMUM_INTERVAL, offDuration) : 0;
  mBlinks = blinks;
  mPauseDuration = pauseDuration ? max(MINIMUM_INTERVAL, pauseDuration) : 0;
  ;
  mSequences = sequences;
  mFinishedCallbackFunction = finishedCallbackFunction;
  mStartTime = max(millis(), 1);
  mLastRunTime = 0;
  update();
}

void EasyLed::on()
{
  blink(1, 0, 1, 0, 0, NULL);
}

void EasyLed::off()
{
  blink(0, 0, 0, 1, 0, NULL);
}

void EasyLed::onUntil(unsigned int const onDuration, void (*finishedCallbackFunction)())
{
  blink(onDuration, 0, 1, 0, 1, finishedCallbackFunction);
}

void EasyLed::offUntil(unsigned int const offDuration, void (*finishedCallbackFunction)())
{
  blink(0, 0, 0, offDuration, 1, finishedCallbackFunction);
}

void EasyLed::update()
{
  unsigned long currentTime = millis();

  if (currentTime - mLastRunTime < MINIMUM_INTERVAL)
  {
    return;
  }
  mLastRunTime = currentTime;
  if (!mStartTime || !mPin)
  {
    return;
  }

  unsigned long elapsedTime = currentTime - mStartTime;
  unsigned int blinkDuration = mOnDuration + mOffDuration;
  unsigned int sequenceDuration = blinkDuration * mBlinks + mPauseDuration - mOffDuration;

  if (!sequenceDuration ||
      (mSequences != 0 && elapsedTime / sequenceDuration >= mSequences))
  {
    mStartTime = 0;
    if (mFinishedCallbackFunction)
    {
      mFinishedCallbackFunction();
    }
    return;
  }

  // Figure out where we are within a sequence
  unsigned int blinkingDuration = blinkDuration * mBlinks;
  unsigned int timeInSequence = elapsedTime % sequenceDuration;
  if (timeInSequence < blinkingDuration && timeInSequence % blinkDuration < mOnDuration)
  {
    if (mPolarity == COMMON_NEGATIVE)
    {
      digitalWrite(mPin, HIGH);
    }
    else if (mPolarity == COMMON_POSITIVE)
    {
      digitalWrite(mPin, LOW);
    }
  }
  else
  {
    if (mPolarity == COMMON_NEGATIVE)
    {
      digitalWrite(mPin, LOW);
    }
    else if (mPolarity == COMMON_POSITIVE)
    {
      digitalWrite(mPin, HIGH);
    }
  }
}