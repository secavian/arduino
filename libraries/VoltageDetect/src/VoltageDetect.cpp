#include <VoltageDetect.h>

VoltageDetect::VoltageDetect(float r1, float r2, float ref_volts, uint8_t pin) : _pin(pin) {
    //sample values
    //r1 = 100000 ohms (brn blk yel)
    //r2 = 22000 ohms  (red red org)
    
    //resistors = (r1 + r2) / r2
    //resistors = (100000 + 22000) / 22000 = 5.54545455
    //note the resistance formula is the inverse of the normal. we're working backwards here.

    //ref volts = 3.3
    //operating volts = ref volts / 1023         (1023 is the value we would see on an analog pin if we connect to 3.3v)
    //operating volts = 3.3 / 1023 = 0.00322581  (1023 is the value we would see on an analog pin if we connect to 3.3v)

    //vref = operating volts * resistors
    //vref = .00322581 * 5.54545455 = 0.017888583
    
    //this value doesn't make sense, but let's protect against a divide by zero error anyway
    if(r2 == 0){ r2 = 1; }
    
    float resistors = (r1 + r2) / r2;
    float operatingVolts = ref_volts / 1023.0F;
    _vref = operatingVolts * resistors;
}

float VoltageDetect::read() const{
    return analogRead(_pin) * _vref;
}
