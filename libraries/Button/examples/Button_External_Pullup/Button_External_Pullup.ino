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
 GND >------[ R1 ]----[ LED1 +]-------> Digital Pin 11
 
              ___|___
 GND >--------+ SW1 +------+----------> Digital Pin 8
                           |
                           +--[ R2 ]--> Vcc
*********************/


Led led(11);
Button button(12, Pullup);

void setup(){ }

void loop() {
    led.OnWhen(button.Pressed());
}


