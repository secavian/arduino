#include <Led.h>
#include <Button.h>

/*********************
Use a button to toggle an LED on or off.

This sketch does not use the button to toggle the LED directly.
Rather, it is read in as a digital input which is used in turn
to toggle the LED on or off as appropriate.

Note that this sketch uses the internal pullup resistor of the
arduino.

===============================================
CIRCUIT

 GND >------[ R1 ]----[ LED1 +]-------> Digital Pin 11
 
              ___|___
 GND >--------+ SW1 +-----------------> Digital Pin 12

 
 *********************/

Led led(11);
ToggleButton button(12);

void setup(){
    Serial.begin(9600);
    
    button.On(true);
}

void loop() {
    led.OnWhen(button.On());
    
    if(button.Toggled()){ Serial.println("toggled"); }
}


