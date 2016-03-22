// 
// 
// 

#include "Button.h"

Button::Button(uint8_t pin) :_pin(pin) {
    pinMode(pin, INPUT);
}

bool Button::Pressed(void) {
    return digitalRead(_pin) == HIGH;
}

uint8_t Button::Pin(void) { return _pin; }
