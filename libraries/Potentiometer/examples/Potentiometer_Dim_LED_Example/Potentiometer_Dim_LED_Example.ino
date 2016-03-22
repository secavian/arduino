#include <Potentiometer.h>
#include <Led.h>

/*********************

Dim an LED using a potentiometer. This sketch does not use the pot
to dim the LED directly. Rather, the value of the pot is read in as
an analog input which is used in turn to set the intensity of the LED

Connect 10K Potentiometer (R1) outer pins to GND and 5v
Connect 10K Potentiometer (R1) inner pin to A0
Connect 330 Ohm Resistor (R2) between ground and negative terminal of LED
Connect Positive terminal of LED to Digital Pin 9 (PWM)

               ____
 GND >--------| R1 |-------> 5v
              |__/_|
                |
                +----------> Analog Pin 0
 
 GND >--------[ R2 ]-------[ LED +]----------> Digital Pin 9
    
    Where:
        R1  = 10K Ohm Potentiometer
        R2  = 330 Ohm Resistor
        LED = LED
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

Led led(9);
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
    
    //dim the led based on the potentiometer setting. we need to scale the value
    //as it between 0 - 1023 whereas the led only accepts a value between 0 - 255
    uint8_t scaledValue = (uint8_t)(((value + 1) / 4.0) - 1);
    
    led.On(scaledValue);
}




