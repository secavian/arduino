#include <Potentiometer.h>
#include <Led.h>

/*********************

Turn an LED on or off using a potentiometer. This sketch does not use the pot
to toggle the LED directly. Rather, the value of the pot is read in as
an analog input which is used in turn to turn the LED on or off

===============================================
CIRCUIT
===============================================
Connect 330 Ohm resistor (R1) between ground and cathode of LED
Connect anode of LED to digital pin 11

 (The cathode is typically the short led on the LED)

 Connect 10K Potentiometer (R2) outer pins to GND and 5v
 Connect 10K Potentiometer (R2) inner pin to A0


 GND >------[ R1 ]----[ LED1 +]-----> Digital Pin 11
               ____
 GND >--------| R2 |-------> 5v
              |__/_|
                |
                +----------> Analog Pin 0
    
    Where:
        R1   = 330 Ohm Resistor
        R2   = 10K Ohm Potentiometer
        LED1 = Red LED
*********************/

//uncomment this line to see the values used to dim the LED in the Serial monitor
//#define DEBUG

Led led(11);
Potentiometer pot(A0);

void setup() {
    #ifdef DEBUG
    Serial.begin(9600);
    #endif
}

void loop() {
    //get a normalized value (returns a value between 0 and 1023 regardless
    //of the actual value read on the pin). be sure to cycle the pot once
    //between its min and max values. otherwise, the value that this function
    //returns is invalid. once the pot has been cycled, it's good to go.
    int16_t value = pot.Value(true);
    
    //toggle the led based on the value read at the pot.
    led.OnWhen(value > 512.0);

    #ifdef DEBUG
    Serial.print("Min:\t"); Serial.print(pot.Min()); Serial.print("\t");
    Serial.print("Max:\t"); Serial.print(pot.Max()); Serial.print("\t");
    Serial.print("Raw Value:\t"); Serial.print(pot.RawValue(), DEC); Serial.print("\t"); 
    Serial.print("Adj Value:\t"); Serial.print(value, DEC); Serial.print("\t"); 
    Serial.print("Led:\t"); Serial.println(led.State() == HIGH ? "On" : "Off");
    delay(50);
    #endif
}




