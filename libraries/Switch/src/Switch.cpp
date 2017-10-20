#include "Switch.h"

Switch::Switch(int8_t pin, SwitchModes mode) :_pin(pin) {
    //switch is on when signal is LOW when using pull up resistor
    _onState = LOW;
    
    switch(mode){
        case Pullup:
            pinMode(pin, INPUT);
            break;
            
        case Pulldown:
            pinMode(pin, INPUT);
            
            //switch is on when signal is HIGH when using pull down resistor
            _onState = HIGH;
            break;
        
        default:
            pinMode(pin, INPUT_PULLUP);
            break;
    }
}

bool Switch::On() {
    return digitalRead(_pin) == _onState;
}

bool Switch::Off() {
    return digitalRead(_pin) != _onState;
}

uint8_t Switch::Pin(void) const { return _pin; }

