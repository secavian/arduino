#ifndef _voltage_detect_h
#define _voltage_detect_h

#if defined(ARDUINO) && ARDUINO >100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class VoltageDetect{
public:
    //this is the circuit diagram            VIN >>--[R1]---+---->> VOUT (to analog pin)
    //R1   = high side resistor                       |     |
    //R2   = low side resistor                       [R2]  [C1]
    //C1   = a 0.1uF capacitor                        |     |
    //VIN  = voltage being checked                   GND   GND
    //VOUT  = voltage delivered to analog pin
    //
    //make sure the voltage drop across R1 is sufficient to lower the max voltage seen at
    //the analog pin to a safe level. don't exceed its tolerance.
    //
    //example:
    //  R1 = 1K
    //  R2 = 1K
    //
    //  Voltage drop across R1 == R1 / (R1 + R2)
    //                         == 1K / 2K
    //                         == .5
    //
    //                      VIN  == 5v
    //                      VOUT == 2.5v        safe for 3.3v and 5v systems
    //
    //                      VIN  == 9v
    //                      VOUT == 4.5v        safe for 5v system - over voltage for 3.3v system!
    //
    //                      VIN  == 12v
    //                      VOUT == 6v          over voltage for all systems!
    //
    //also consider the current drawn across the circuit. low values, even if they make the voltage seen
    //at the analog pin safe, can cause a battery to drain quickly.
    
    VoltageDetect(float r1, float r2, float ref_volts, uint8_t pin);
    
    float read() const;
private:
    uint8_t _pin;
    float _vref;
};

#endif
