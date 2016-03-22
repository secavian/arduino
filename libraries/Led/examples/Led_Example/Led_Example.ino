#include <Led.h>

/*********************

Toggle the LED on the board (pin 13) on and off

*********************/

Led led(13);            //use built in LED on pin 13

void setup() {
}

void loop() {
    led.Toggle();
    delay(250);
}
