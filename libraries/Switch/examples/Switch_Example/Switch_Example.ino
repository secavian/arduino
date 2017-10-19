#include <Led.h>
#include <Switch.h>

/*********************
Use a switch to turn an LED on or off.

This sketch does not use the button to toggle the LED directly.
Rather, it is read in as a digital input which is used in turn
to toggle the LED on or off as appropriate.

Note that this sketch uses the internal pullup resistor of the
arduino.

===============================================
CIRCUIT

 GND >------[ R1 ]----[ LED1 +]-------> Digital Pin 11
 
                  SW1
           ---     | ----
          |      __|__   |
          |  |   |   |   |
           --|---|---|---
             x   |   |
                 |   |
 GND >-----------+   +--------------> Digital Pin 12

 
 *********************/

Led led(11);
Switch switch(12);

void setup(){ }

void loop(){
    led.OnWhen(switch.On());
}


