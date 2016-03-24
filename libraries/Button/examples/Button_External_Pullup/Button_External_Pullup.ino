#include <Led.h>
#include <Button.h>

/*********************

Use a button to turn an LED on or off.
This sketch does not use the button to toggle the LED directly.
Rather, it is read in as a digital input which is used in turn
to toggle the LED on or off as appropriate.

Note that this sketch uses an external pullup resistor on the switch

===============================================
CIRCUIT
===============================================
Connect 330 Ohm resistor (R1) between ground and cathode of LED
Connect anode of LED to digital pin 11
 (The cathode is typically the short led on the LED)
 
Connect momentary contact switch (SW1) between ground and digital pin 8
Connect 10K Ohm resistor (pullup) between pin side of SW1 and 5v

 GND >------[ R1 ]----[ LED1 +]-------> Digital Pin 11
 
              ___|___
 GND >--------+ SW1 +------+----------> Digital Pin 8
                           |
                           +--[ R2 ]--> 5v
    
    Where:
        R1   = 330 Ohm resisotr
        R2   = 10K Ohm resistor
        SW1  = Momentary Contact Switch
        LED1 = Red LED
*********************/


Led led(11);
Button button(12, false);

void setup() {
}

void loop() {
    led.OnWhen(button.Pressed());
}
