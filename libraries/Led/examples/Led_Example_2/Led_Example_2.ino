#include <Led.h>

/*********************

Toggle an LED on and off

===============================================
CIRCUIT
===============================================
Connect 330 Ohm resistor between ground and cathode of Red LED
Connect anode of Red LED to digital pin 11
Connect 330 Ohm resistor between ground and cathode of Green LED
Connect anode of Green LED to digital pin 10
Connect 330 Ohm resistor between ground and cathode of Blue LED
Connect anode of Blue LED to digital pin 9

 (The cathode is typically the short led on the LED)

 GND >------[ R1 ]----[ LED1 +]-----> Digital Pin 11
 GND >------[ R2 ]----[ LED2 +]-----> Digital Pin 10
 GND >------[ R3 ]----[ LED3 +]-----> Digital Pin 9

    Where:
        R1   = 330 Ohm Resistor
        R2   = 330 Ohm Resistor
        R3   = 330 Ohm Resistor
        LED1 = Red LED
        LED2 = Green LED
        LED3 = Blue LED
*********************/

Led redLed(11);
Led greenLed(10);
Led blueLed(9);

void setup() {
}

void loop() {
    uint32_t value = random(1, 4);
    redLed.OnWhen(value == 1);
    greenLed.OnWhen(value == 2);
    blueLed.OnWhen(value > 2);
    delay(250);
}
