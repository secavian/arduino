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
    
    #include <Button.h>
    #include <Led.h>
    
    Led led(11);
    Button button(12);
    
    void setup(){ }
    
    void loop(){
        led.OnWhen(button.Pressed());
    }
    ================================================================================
*/
#ifndef _BUTTON_h
#define _BUTTON_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

/*  buttons need a pull up/down resistor. this can be the
    internal pull up resistor if available (default) or
    an external pull up/down button as appropriate
*/
enum ButtonModes { InternalPullup, Pullup, Pulldown };

/*  Button class to allow simple access to a momentary push button
    to determine if the button is pressed (after allowing for a
    debounce delay).
*/
class Button {
public:
    /*  initializes new instance of Button class on the specified pin
        and enables the internal pullup resistor by default
    */
    Button(int8_t pin) : Button(pin, InternalPullup){}
    
    /*  initializes new instance of Button class on the specified pin.
        
        allows the use of a button with an external pull up or pull down resistor
        by passing in the desired mode directly.
    
        * InternalPullup
        * Pullup
        * Pulldown
        
        if a pull up resistor is used (internal or external), button
        considered pressed if pin is LOW. if a pull down resistor
        is used, button is considered pressed if pin is HIGH
    */
    Button(int8_t pin, ButtonModes mode);
    
    /*  gets if the button is pressed. compenstates for bounce */
    bool Pressed(void);
    
    /*  buttons tend to bounce, so a default delay of 50ms is used whenever
        reading a digital pin in order to avoid spurious readings. increase
        or decrease the debounce delay as needed here.
    */
    void DebounceDelay(uint32_t d);
    
    /* gets the assigned pin for this instance */
    uint8_t Pin(void) const;
protected:
    int8_t _pin;
    int _onState;
    uint32_t _debounceDelay = 50;
};

/*  Extends the Button class to allow a momentary push button to behave
    like a switch (toggle, switch, etc.)
*/
class ToggleButton : public Button {
public:
    /*  initializes new instance of Button class on the specified pin
        and enables the internal pullup resistor by default
    */
    ToggleButton(uint8_t pin) : Button(pin){}
    
    /*  initializes new instance of Button class on the specified pin.
        
        allows the use of a button with an external pull up or pull down resistor
        by passing in the desired mode directly.
    
        * InternalPullup
        * Pullup
        * Pulldown
        
        if a pull up resistor is used (internal or external), button
        considered pressed if pin is LOW. if a pull down resistor
        is used, button is considered pressed if pin is HIGH
    */
    ToggleButton(uint8_t pin, ButtonModes mode) : Button(pin, mode){}
    
    /*  gets the on/off state of the button */
    bool On(void);
    
    /*  sets the on/off state of the button */
    void On(bool on);
    
    /*  gets if the state of the button changed */
    bool Toggled(void) const;
protected:
    bool _on;
    bool _lastState;
    bool _toggled;
};

#endif

