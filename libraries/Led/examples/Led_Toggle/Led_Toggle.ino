#include <Led.h>

/*********************
Toggle an LED on and off
*********************/

Led led(LED_BUILTIN);

void setup() {
}

void loop() {
    led.Toggle();
    delay(250);
}
