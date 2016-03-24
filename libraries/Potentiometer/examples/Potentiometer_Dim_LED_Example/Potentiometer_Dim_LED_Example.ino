#include <Potentiometer.h>
#include <Led.h>

/*********************

Dim an LED using a potentiometer. This sketch does not use the pot
to dim the LED directly. Rather, the value of the pot is read in as
an analog input which is used in turn to set the intensity of the LED

If a standard potentiometer is being used, leave the 
#define USE_AUTO_CENTER_POTENTIOMETER macro line commented out.
The 'red' led in this case is not used. Instead, the pot will
control the brightness of the green led as it is cycled through
its range of motion.

If an auto-centering potentiomenter is being used, uncomment the
#define USE_AUTO_CENTER_POTENTIOMETER macro line. Both the green
and 'red' LEDs are used in this case. The pot will control the
brightness of the green led when it is between the center value
and the full value. It will control the red led when it is between
the center value and the off value.

===============================================
CIRCUIT
===============================================

Connect 10K Potentiometer (R1) outer pins to GND and 5v
Connect 10K Potentiometer (R1) inner pin to A0
Connect 330 Ohm Resistor (R2) between ground and negative terminal of LED 1 ("greenLed")
Connect Positive terminal of LED 1 to Digital Pin 10 (PWM)
Connect 330 Ohm Resistor (R3) between ground and negative terminal of LED 2 ("redLed")
Connect Positive terminal of LED 2 to Digital Pin 11 (PWM)

               ____
 GND >--------| R1 |-------> 5v
              |__/_|
                |
                +----------> Analog Pin 0
 
 GND >--------[ R2 ]-------[ LED1 +]----------> Digital Pin 10
 GND >--------[ R3 ]-------[ LED2 +]----------> Digital Pin 11
    
    Where:
        R1   = 10K Ohm Potentiometer
        R2   = 330 Ohm Resistor
        R3   = 330 Ohm Resistor
        LED1 = Green LED
        LED2 = Red LED
*********************/
//uncomment this line to see the values used to dim the LED in the Serial monitor
//#define DEBUG

//uncomment this line to use an autocentering potentiometer
#define USE_AUTO_CENTER_POTENTIOMETER

Led systemLed(13);
Led greenLed(10);

#ifdef USE_AUTO_CENTER_POTENTIOMETER
    AutoCenterPotentiometer pot(A0);
    Led redLed(11);
#else
    Potentiometer pot(A0);
#endif


void setup() {
    #ifdef DEBUG
    Serial.begin(9600);
    #endif

    #ifdef USE_AUTO_CENTER_POTENTIOMETER
    pot.FindCenter(100);
    #endif
    
    //indicate system is ready to use
    systemLed.On();
}

void loop() {
    //get a normalized value (returns a value between 0 and 1023 regardless
    //of the actual value read on the pin). be sure to cycle the pot at least once
    //between its min and max values. otherwise, the value that this function
    //returns is invalid. once the pot has been cycled, it's good to go.
    //
    //note that if #define USE_AUTO_CENTER_POTENTIOMETER is in effect, the value
    //returned from the pot is between -511 to +511 (with 0 indicating the pot
    //is in the center position)
    int16_t value = pot.Value(true);
    
    #ifdef USE_AUTO_CENTER_POTENTIOMETER
        //dim the led based on the potentiometer setting. we need to scale the value
        //as it is between -512 to +512 whereas the led only accepts a value between 0 - 255
        //also, we only want to turn on the green led when the value is positive and the
        //red led when the value is negative.
        
        uint8_t scaledValue = (uint8_t)map(abs(value), 0, 512, 0, 255);
        if(value > 0) { redLed.Off(); greenLed.On(scaledValue); }
        else { greenLed.Off(); redLed.On(scaledValue); }
    #else
        //dim the led based on the potentiometer setting. we need to scale the value
        //as it is between 0 - 1023 whereas the led only accepts a value between 0 - 255
        uint8_t scaledValue = (uint8_t)map(value, 0, 1023, 0, 255);
        greenLed.On(scaledValue);
    #endif

    #ifdef DEBUG
        Serial.print("Min:\t"); Serial.print(pot.Min()); Serial.print("\t");
        Serial.print("Max:\t"); Serial.print(pot.Max()); Serial.print("\t");
        #ifdef USE_AUTO_CENTER_POTENTIOMETER
            Serial.print("CTR Min:\t"); Serial.print(pot.CenterMin(), DEC); Serial.print("\t"); 
            Serial.print("CTR MAX:\t"); Serial.print(pot.CenterMax(), DEC); Serial.print("\t"); 
        #endif
        Serial.print("Raw Value:\t"); Serial.print(pot.RawValue(), DEC); Serial.print("\t"); 
        Serial.print("Adj Value:\t"); Serial.print(value, DEC); Serial.print("\t"); 
        Serial.print("Scaled Value:\t"); Serial.print(scaledValue, DEC);
        Serial.println(" .");
        delay(50);
    #endif
}




