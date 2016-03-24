#include "Potentiometer.h"

Potentiometer::Potentiometer(int8_t pin) : _pin(pin) { }

int16_t Potentiometer::RawValue(){ return _rawValue; }
int16_t Potentiometer::Max(){ return _max; }
int16_t Potentiometer::Min(){ return _min; }
int8_t Potentiometer::Pin(){ return _pin; }

int16_t Potentiometer::Value() { return Value(false); }
int16_t Potentiometer::Value(bool normalize) { 
    if(_pin < 0) { return 0; }
    
    _rawValue = analogRead(_pin); 
    if(normalize){
        if(_rawValue > _max) { _max = _rawValue; }
        if(_rawValue < _min) { _min = _rawValue; }
        
        return (int16_t)map(_rawValue, _min, _max, 0, 1023);
    }
    
    return _rawValue;
}
