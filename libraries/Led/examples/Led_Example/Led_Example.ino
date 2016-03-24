#include <Led.h>

/*********************

Toggle an LED on and off

===============================================
CIRCUIT
===============================================
Connect 330 Ohm resistor between ground and cathode of LED
Connect anode of LED to digital pin 11

 (The cathode is typically the short led on the LED)

 GND >------[ R1 ]----[ LED1 +]-----> Digital Pin 11

    Where:
        R1   = 330 Ohm Resistor
        LED1 = Red LED
*********************/

Led led(11);

void setup() {
}

void loop() {
    led.Toggle();
    delay(250);
}
