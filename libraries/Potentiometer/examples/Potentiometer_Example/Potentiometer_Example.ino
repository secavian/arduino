#include <Potentiometer.h>
#include <Led.h>

/*********************

Turn an LED on or off using a potentiometer. This sketch does not use the pot
to toggle the LED directly. Rather, the value of the pot is read in as
an analog input which is used in turn to turn the LED on or off

Connect 10K Potentiometer (R1) outer pins to GND and 5v
Connect 10K Potentiometer (R1) inner pin to A0

 GND >--------[ R1 ]-------> 5v
                 /
                |
                +----------> Analog Pin 0
    
    Where:
        R1  = 10K Ohm Potentiometer
*********************/


//define analog pins
#define A0                      0
#define A1                      1
#define A2                      2
#define A3                      3
#define A4                      4
#define A5                      5
#define A6                      6
#define A7                      7

Led led(13);                //Use System LED
Potentiometer pot(A0);

void setup() {
    Serial.begin(9600);
}

void loop() {
    //get a normalized value (returns a value between 0 and 1023 regardless
    //of the actual value read on the pin). be sure to cycle the pot once
    //between its min and max values. otherwise, the value that this function
    //returns is invalid. once the pot has been cycled, it's good to go.
    double value = pot.Value(true);
    
    //toggle the led based on the value read at the pot.
    led.On(value > 512.0);
}




