// Led.h

#ifndef _LED_h
#define _LED_h

#if defined(ARDUINO) && ARDUINO >= 100
    #include "arduino.h"
#else
    #include "WProgram.h"
#endif

class Led {
public:
    //initializes new instance of Led class
    Led(uint8_t pin);
    
    //turns the LED on
    void On(void);
    
    //turns the LED on based on value of 'on' parameter
    //if on is true, turn LED on, else turn LED off
    void On(bool on);
    
    //turns the bool on at a given intensity. LED pin must
    //be a PWM pin (~) for this function to work.
    //0 == off, 255 == full
    void On(uint8_t intensity);
    
    //turns the LED on based on value of 'on' parameter
    //if on is true, turn LED on, else turn LED off at
    //the intensity level specified. LED pin must
    //be a PWM pin (~) for this function to work.
    //0 == off, 255 == full
    void On(bool on, uint8_t intensity);
    
    //turns the LED off
    void Off(void);
    
    //toggles the state of the LED
    void Toggle(void);
    
    //gets the value of the assigned pin
    uint8_t Pin(void);
    
    //gets the value of the current state (if on, returns HIGH, else return LOW);
    uint8_t State(void);

private:
    uint8_t _pin;
    uint8_t _state;
};

#endif

