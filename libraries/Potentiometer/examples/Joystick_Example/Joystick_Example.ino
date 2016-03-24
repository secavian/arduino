#include <Potentiometer.h>
#include <Led.h>

/*********************

Dim two LEDs using a joystick. This sketch does not use the joystick
to dim the LEDs directly. Rather, the value of the joystick is read in as
analog inputs which are used in turn to set the intensity of the LEDs

Turn an LED on or off using a joystick button

Note that the joystick is treated as a type of button
with two autocentering potentiometers connected to it.

If the joystick in quesion does not have a button function,
simply pass in the two analog pins for the pots and be
done with it.

===============================================
CIRCUIT
===============================================

Connect joystick (R1) approriate pins to GND and 5v
Connect joystick (R1) x axis pin to A0
Connect joystick (R1) y axis pin to A1
Connect joystick (R1) button pin to 12
Connect 330 Ohm Resistor (R2) between ground and negative terminal of LED 1 ("greenLed")
Connect Positive terminal of LED 1 to Digital Pin 10 (PWM)
Connect 330 Ohm Resistor (R3) between ground and negative terminal of LED 2 ("redLed")
Connect Positive terminal of LED 2 to Digital Pin 11 (PWM)
Connect 330 Ohm Resistor (R4) between ground and negative terminal of LED 3 ("blueLed")
Connect Positive terminal of LED 3 to Digital Pin 9 (PWM)

                +-----------------> Analog Pin 0 (X)
               _|___
              | /   |
 GND >--------| R1  |-------------> 5v
              |__/__|
                |  |
                |  +---+----------> Digital Pin 12 (Button)
                |
                +-----------------> Analog Pin 1 (Y)
 
 GND >--------[ R2 ]-------[ LED1 +]----------> Digital Pin 10 ("greenLed")
 GND >--------[ R3 ]-------[ LED2 +]----------> Digital Pin 11 ("redLed")
 GND >--------[ R4 ]-------[ LED3 +]----------> Digital Pin 9  ("blueLed")
    
    Where:
        R1   = 10K Ohm 2 Axis Joystick with select button
        R2   = 330 Ohm Resistor
        R3   = 330 Ohm Resistor
        R4   = 330 Ohm Resistor
        LED1 = Green LED
        LED2 = Red LED
        LED3 = Blue LED
*********************/

Led blueLed(9);             //controlled by pressing joystick button
Led greenLed(10);           //controlled by joystick x axis pot
Led redLed(11);             //controlled by joystick y axis pot

Joystick js(A0, A1, 12);

void setup() {
}

void loop() {
    //get normalized values (returns a value between -512 and +512 regardless
    //of the actual value read on the pins). be sure to cycle the pots at least once
    //between their min and max values. otherwise, the value that the X.Value() and Y.Value()
    //functions return are invalid. once the pot have been cycled, they're good to go.
    int8_t xValue = (uint8_t)map(abs(js.X.Value(true)), 0, 512, 0, 255);
    int8_t yValue = (uint8_t)map(abs(js.Y.Value(true)), 0, 512, 0, 255);
    bool pressed = js.Pressed();
    
    //toggle the led based on the value read at the X/Y pots. centering a pot
    //will turn off the assoaciated led. increasing or decreasing the pot (moving it
    //away from the center postion) will increase the brightness of the led
    greenLed.On(xValue);
    redLed.On(yValue);
    
    //toggle on or off when the joystick is pressed
    blueLed.OnWhen(pressed);
}




