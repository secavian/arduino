#include <VoltageDetect.h>

#define R1             1000        //1k ohms
#define R2             1000        //1k ohms
#define REF_VOLTS      5           //5 volts
#define ANALOG_PIN     A0          //analog pin 0

//Circuit diagram:
//
//      VIN >>--[1K]---+-------->> A0
//                     |
//                     +--[1K]-->> GND
//
//maximum safe volts: 10v.
//likely less due to resistor tolerances

VoltageDetect volts(R1, R2, REF_VOLTS, ANALOG_PIN);

void setup(){
    Serial.begin(9600);
}

void loop(){
    Serial.println(volts.read());
    delay(500);
}
