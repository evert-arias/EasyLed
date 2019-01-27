# EasyLed Arduino Library

[![License](http://img.shields.io/:license-mit-blue.svg)](http://doge.mit-license.org)

Simple LED  library for the Arduino platform.

## Introduction

This library allows you to perform blinking operations with LEDs.

### The Class

The **EasyLed** class allows you to create an instance of the LED you want to operate. The class constructor takes two values as arguments. The **first argument** is the pin where the LED is connected. The **second argument** is **optional** to define the polarity of the LED. If this argument is not provided, the LED polarity will be set to common negative by default.

```cpp
/* EasyLed Instance.
 * First argument: The pin where the LED is connected.
 * Second argument: Optional argument to define the LED polarity.
   Allowed values:
                  COMMON_NEGATIVE
                  COMMON_POSITIVE
 */
EasyLed led(13, COMMON_POSITIVE);
```

### Methods

```cpp
/* Set the pin where the LED is connected. */
led.setPin(pin);
```

```cpp
/* Set the LED polarity.
 * Allowed values: COMMON_NEGATIVE, COMMON_POSITIVE.
 */
led.setPolarity(COMMON_NEGATIVE);
```

```cpp
/* Turn On the LED. */
myBlueLed.on();
```

```cpp
/* Turn Off the LED. */
led.off();
```

```cpp
/* Turn On the LED for the time of "onDuration" then call the "onFinished" method. */
led.onUntil(onDuration, onFinished);
```

```cpp
/* Turn Off the LED for the time of "offDuration" then call the "onFinished" method. */
led.offUntil(offDuration, onFinished);
```

```cpp
/* Blink the LED.
 * The LED will be On for the time of "onDuration".
 * The LED will be Off for the time of "offDuration".
 * That blink will be repeated the number of times defined by "blinks".
 * Then a pause define by "pauseDuration".
 * That sequency will repeat as many time as defined by "sequences".
 * At the end of all sequences the "onFinished" method will be called.
 */
 led.blink(onDuration, offDuration, blinks, pauseDuration, sequences, onFinished);
```

```cpp
 /* Allways call this method in the loop. */
 led.update();
```



## Copyright

[MIT](https://github.com/ariascode/MyBlinker/blob/master/LICENSE.md) © [Evert Arias](https://ariascode.com)
