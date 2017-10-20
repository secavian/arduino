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
    
    #include <Switch.h>
    #include <Led.h>
    
    Led led(11);
    Switch switch(12);
    
    void setup(){ }
    
    void loop(){
        led.OnWhen(switch.On());
    }
    ================================================================================
*/
#ifndef _SWITCH_h
#define _SWITCH_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

/*  Switches need a pull up/down resistor. this can be the
    internal pull up resistor if available (default) or
    an external pull up/down resistor as appropriate
*/
enum SwitchModes { InternalPullup, Pullup, Pulldown };

/*  Class to abstract switch in code
*/
class Switch {
public:
    /*  initializes new instance of Switch class on the specified pin
        and enables the internal pullup resistor by default
    */
    Switch(int8_t pin) : Switch(pin, InternalPullup){}
    
    /*  initializes new instance of Switch class on the specified pin.
        
        allows the use of a switch with an external pull up or pull down resistor
        by passing in the desired mode directly.
    
        * InternalPullup
        * Pullup
        * Pulldown
        
        if a pull up resistor is used (internal or external), switch
        considered pressed if pin is LOW. if a pull down resistor
        is used, switch is considered pressed if pin is HIGH
    */
    Switch(int8_t pin, SwitchModes mode);
    
    /*  gets if the switch is pressed. no debounce compensation */
    bool On(void);
    
    /*  gets if the switch is un pressed. no debounce compensation */
    bool Off(void);
    
    /* gets the assigned pin for this instance */
    uint8_t Pin(void) const;
protected:
    int8_t _pin;
    int _onState;
};

#endif

