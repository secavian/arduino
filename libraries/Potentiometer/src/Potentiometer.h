#ifndef _POTENTIOMETER_H_
#define _POTENTIOMETER_H_

#if defined(ARDUINO) && ARDUINO >= 100
    #include "arduino.h"
#else
    #include "WProgram.h"
#endif

class Potentiometer{
public:
    //initialized new instance of Potentiometer class
    Potentiometer(uint8_t pin) : _pin(pin) { }
    
    //returns the value read at the analog pin
    double Value() { return Value(false); }
    
    //returns the value read at analog pin normalized to return
    //a value between 0 and 1023. cycle the potentiometer at least
    //once between the max and min values if this function is called
    //as the value returned is otherwise invalid.
    double Value(bool normalize);
    
    
private:
    uint8_t _pin;
    uint16_t _max = 0;
    uint16_t _min = 1023;
};

#endif