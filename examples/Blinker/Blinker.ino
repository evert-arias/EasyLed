/*
  EasyLed - Led Blinker Example

  Simple sketch to demostrate how to blink an LED with EasyLed library.

  The circuit: An LED attached to pin 27

  https://github.com/evert-arias/EasyLed

*/

#include "EasyLed.h"

const int ledPin = 27;	// Arduino pin where the LED is connected

EasyLed led(ledPin);

/* setup */
void setup() {
  // Blink
  led.blink(500  /* time on */,
            100  /* time off */,
            3    /* cycles */,
            1000 /* pause between sequences */,
            2    /* sequences */,
            NULL /* function to call when finished */
           );
}

/* loop */
void loop() {
  // Always call the "update" function in the loop
  led.update();
}
