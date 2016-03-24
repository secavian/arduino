#ifndef _POTENTIOMETER_H_
#define _POTENTIOMETER_H_

#if defined(ARDUINO) && ARDUINO >= 100
    #include "arduino.h"
#else
    #include "WProgram.h"
#endif

#include <Button.h>

class Potentiometer{
public:
    //initialized new instance of Potentiometer class
    Potentiometer(int8_t pin);
    
    //returns the value read at the analog pin
    int16_t Value();
    
    //returns the value read at analog pin normalized to return
    //a value between 0 and 1023. cycle the potentiometer at least
    //once between the max and min values if this function is called
    //as the value returned is otherwise invalid.
    int16_t Value(bool normalize);
    
    //gets the actual value read on the analog pin
    int16_t RawValue();
    
    //gets the minimum value read from the analog pin
    int16_t Max();
    
    //gets the minimum value read from the analog pin
    int16_t Min();
    
    //gets the assigned pin for this instance
    int8_t Pin();
    
protected:
    int8_t _pin;
    int16_t _max = 0;
    int16_t _min = 1023;
    int16_t _rawValue = 0;
};

class AutoCenterPotentiometer : public Potentiometer{
public:
    AutoCenterPotentiometer(int8_t pin);
    
    int16_t Center();
    int16_t CenterMin();
    int16_t CenterMax();
    
    void FindCenter();
    void FindCenter(uint8_t resolution);
    
    int16_t Value(bool normalize);
protected:
    int16_t _center;
    int16_t _centerMin = 1023;
    int16_t _centerMax = 0;
    bool _centerFound = false;
};

class Joystick : public Button{
public:
    Joystick(int8_t xPin, int8_t yPin);
    Joystick(int8_t xPin, int8_t yPin, int8_t buttonPin);
    
    AutoCenterPotentiometer X;
    AutoCenterPotentiometer Y;
private:
};

#endif