// 
// 
// 

#include "Button.h"

Button::Button(int8_t pin) : Button(pin, true) { }

Button::Button(int8_t pin, bool enableInternalPullupResistor) :_pin(pin) {
    if(pin < 0){ return; }
    if(enableInternalPullupResistor){
        pinMode(pin, INPUT_PULLUP);
        _useIntPullup = true;
    }
    else{
        pinMode(pin, INPUT);
    }
}

void Button::PressedOnHigh(bool pressedOnHigh){
    _pressedOnHigh = pressedOnHigh;
}

bool Button::PressedOnHigh() {
    return _pressedOnHigh;
}

bool Button::Pressed(void) {
    if(_pin < 0) { return false; }
    if(_useIntPullup){
        return digitalRead(_pin) == _useIntPullup ? LOW : HIGH;
    }
    return digitalRead(_pin) == _pressedOnHigh ? HIGH : LOW;
}

int8_t Button::Pin(void) { return _pin; }
