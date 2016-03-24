#include "Potentiometer.h"

AutoCenterPotentiometer::AutoCenterPotentiometer(int8_t pin) : Potentiometer(pin) { }

int16_t AutoCenterPotentiometer::Center(){ return _center; }
int16_t AutoCenterPotentiometer::CenterMin(){ return _centerMin; }
int16_t AutoCenterPotentiometer::CenterMax(){ return _centerMax; }

void AutoCenterPotentiometer::FindCenter() { FindCenter(10); }
void AutoCenterPotentiometer::FindCenter(uint8_t resolution){
    if(_pin < 0){ return; }
    
    int32_t value = 0;
    for(int i = 0; i < resolution; i++){
        int16_t readvalue = analogRead(_pin);
        if(readvalue > _centerMax) { _centerMax = readvalue; }
        if(readvalue < _centerMin) { _centerMin = readvalue; }
        delay(1);
        
        value += readvalue;
    }
    
    _center = value / resolution;
    _centerFound = true;
}

int16_t AutoCenterPotentiometer::Value(bool normalize) { 
    if(_pin < 0){ return 0; }
    
    if(_centerFound == false) { FindCenter(10); }
    
    _rawValue = analogRead(_pin); 
    if(normalize){
        if(_rawValue > _max) { _max = _rawValue; }
        if(_rawValue < _min) { _min = _rawValue; }
        
        if(_rawValue > _centerMax) {
            return (int16_t)map(_rawValue, _centerMax, _max, 1, 511);
        }
        else if(_rawValue < _centerMin){
            return (int16_t)map(_rawValue, _min, _centerMin, 1, 511) - 512;
        }
        else{ return 0; }
    }
    
    return _rawValue;
}




