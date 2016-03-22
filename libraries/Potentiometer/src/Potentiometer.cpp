#include "Potentiometer.h"

double Potentiometer::Value(bool normalize) { 
    int value = analogRead(_pin); 
    if(normalize){
        if(value > _max) { _max = value; }
        if(value < _min) { _min = value; }

        double range = _max - _min;
        value = ((value - _min) / range) * 1023;
    }
    
    return value;
}
