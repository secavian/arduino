#include "Button.h"

Button::Button(int8_t pin, ButtonModes mode) :_pin(pin) {
    //button is on when signal is LOW when using pull up resistor
    _onState = LOW;
    
    switch(mode){
        case Pullup:
            pinMode(pin, INPUT);
            break;
            
        case Pulldown:
            pinMode(pin, INPUT);
            
            //button is on when signal is HIGH when using pull down resistor
            _onState = HIGH;
            break;
        
        default:
            pinMode(pin, INPUT_PULLUP);
            break;
    }
}

bool Button::Pressed() {
    int state = digitalRead(_pin);
    
    delay(_debounceDelay);
    
    return state == _onState;
}

void Button::DebounceDelay(uint32_t d){ _debounceDelay = d; }

uint8_t Button::Pin(void) const { return _pin; }


bool ToggleButton::On() {
    _toggled = false;
    int state = digitalRead(_pin);
    
    if(state == _onState){
        _on = !_on;
        _toggled = true;
    }
    
    while(state == _onState){
        delay(_debounceDelay);
        state = digitalRead(_pin);
    }
    
    return _on;
}

void ToggleButton::On(bool on){
    _on = on;
}

bool ToggleButton::Toggled() const { return _toggled; }



