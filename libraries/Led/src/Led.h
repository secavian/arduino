/*
    Software License Agreement (BSD License)

    Copyright (c) 2017, Ralf Thompson
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.
    
    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
    
    ================================================================================
    
    SAMPLE USAGE:
    
    #include <Led.h>
    
    Led led(LED_BUILTIN);
    
    void setup(){}
    
    void loop(){
        led.Toggle();
        delay(500);
    }
    ================================================================================
*/
#ifndef _LED_h
#define _LED_h

#if defined(ARDUINO) && ARDUINO >= 100
    #include "arduino.h"
#else
    #include "WProgram.h"
#endif

class Led {
public:
    //initializes new instance of Led class on the specified pin
    Led(uint8_t pin);
    
    //initializes new instance of Led class on the specified pin
    //and sets the initial state to HIGH or LOW based on 'on' parameter
    Led(uint8_t pin, bool on);
    
    //turns the LED on
    void On(void);
        
    //turns the LED on based on value of 'on' parameter
    //if 'on' is true, turn LED on, else turn LED off
    void OnWhen(bool on);

    //turns the LED on based on value of 'on' parameter
    //if 'on' is true, turn LED on, else leave LED in current state
    void OnIf(bool on);
    
    //turns the LED on at a given intensity. LED pin must
    //be a PWM pin (~) for this function to work.
    //0 == off, 255 == full
    void On(uint8_t intensity);
    
    //turns the LED on based on value of 'on' parameter
    //if 'on' is true, turn LED on, else turn LED off at
    //the intensity level specified. LED pin must
    //be a PWM pin (~) for this function to work.
    //0 == off, 255 == full
    void OnWhen(bool on, uint8_t intensity);
    
    //turns the LED on based on value of 'on' parameter
    //if 'on' is true, turn LED on, else leave LED in current state
    //the intensity level specified. LED pin must
    //be a PWM pin (~) for this function to work.
    //0 == off, 255 == full
    void OnIf(bool on, uint8_t intensity);
    
    //turns the LED off
    void Off(void);

    //turns the LED off based on value of 'off' parameter
    //if 'off' is true, turn LED off, else leave LED in current state
    void OffIf(bool off);
    
    //toggles the state of the LED
    void Toggle(void);
    
    //toggles the state of the LED based on value of 'toggle' parameter
    //if 'toggle' is true, LED is toggled
    void ToggleWhen(bool toggle);
    
    //returns boolean test for State() == HIGH
    bool IsOn();
    
    //gets the value of the assigned pin
    uint8_t Pin(void);
    
    //gets the value of the current state (if on, returns HIGH, else return LOW);
    uint8_t State(void);

private:
    uint8_t _pin;
    uint8_t _state;
};

#endif

