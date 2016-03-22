#include <Led.h>
#include <Button.h>

/*********************

Use a button to turn the LED on the board (pin 13) on or off.
This sketch does not use the button to toggle the LED directly.
Rather, it is read in as a digital input which is used in turn
to toggle the LED on or off as appropriate.

Connect 1K resister (R1) to pin 2
Connect switch between pin 2 and 5v

 GND >--------[ R1 ]-------+-------> Digital Pin 2
                           |
                           |
                            |- [ SW1 ]
                           |
                           ^
                           5v
    
    Where:
        R1  = 1K Ohm Resistor
        SW1 = Momentary Contact Switch
*********************/


Led led(13);            //use built in LED on pin 13
Button button(2);       //button connected to pin 2    

void setup() {
}

void loop() {
    led.On(button.Pressed());
}
