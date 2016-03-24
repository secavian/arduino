// ButtonSpst.h

#ifndef _BUTTON_h
#define _BUTTON_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Button {
public:
    //initializes new instance of Button class on the specified pin
    //and enables the internal pullup resistor by default
    Button(int8_t pin);
    
    //initializes new instance of Button class on the specified pin
    //and enables the internal pullup resistor as specified
    Button(int8_t pin, bool enableInternalPullupResistor);
    
    //this library assumes that switches attached to digital pins will
    //use the internal pull up resistors. if that isn't the case and a
    //external pull DOWN resistor is used instead, pass TRUE into this
    //method so that the library knows to report true for Pressed when
    //the digital pin is LOW (the oposite of the default which is to
    //return true when the digital pin is HIGH).
    void PressedOnHigh(bool pressedOnHigh);
    
    //gets the value passed in
    bool PressedOnHigh();
    
    //gets if the button is pressed
    bool Pressed(void);
    
    //gets the assigned pin for this instance
    int8_t Pin(void);
private:
    int8_t _pin;
    bool _useIntPullup = false;
    bool _pressedOnHigh = false;
};

#endif

