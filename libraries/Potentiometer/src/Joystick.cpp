#include "Potentiometer.h"

Joystick::Joystick(int8_t xPin, int8_t yPin) :
    X(xPin), Y(yPin), Button(-1)
    {}
Joystick::Joystick(int8_t xPin, int8_t yPin, int8_t buttonPin):
    X(xPin), Y(yPin), Button(buttonPin)
    {}



