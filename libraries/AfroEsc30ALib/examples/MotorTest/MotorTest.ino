#include <AfroEsc30ALib.h>
#include <Led.h>
#include <XBee2.h>

//  ***********************************
//  teensy 3.x
//  ***********************************

static const uint16_t minPulseWidth = 1060;
static const uint16_t maxPulseWidth = 1860;
static const uint16_t armPulseWidth = 1000;

ESCLib motor(23, minPulseWidth, maxPulseWidth);
Led g(22);

void setup(){
    Serial.begin(9600);
    
    motor.arm(armPulseWidth);
    delay(1000);
    motor.off();
}

void loop(){
    int val = analogRead(A1);
    uint8_t intensity = map(val, 0, 1023, 0, 255);
    uint16_t throttle = map(val, 0, 1023, minPulseWidth, maxPulseWidth);
    
    Serial.print("A1 val: ");Serial.print(val);
    Serial.print("\tintens: ");Serial.print(intensity);
    Serial.print("\tthrot: ");Serial.println(throttle);
    
    g.On(intensity);
    motor.setThrottle(throttle);
}


