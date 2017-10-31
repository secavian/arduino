/*
Software License Agreement (BSD License)

Copyright (c) 2017, Ralf Thompson
All rights reserved.

Sample program to demonstate how to use this library.

Uses custom libraries for timing and I2C connectivity. Ensure
the following libraries are installed:

I2CLib.h        I2CLib.cpp
SimpleTimer.h   SimpleTimer.cpp
Button.h        Button.cpp

*/

#include <Serial7Segment.h>
#include <SimpleTimer.h>
#include <Button.h>

//comment out this line to make this a stop watch type display
//#define COUNTDOWN

//comment this line to use minutes / seconds
//#define HOURS_MINUTES

Serial7Segment display;
uint16_t counter;
SimpleTimer timer;
SimpleTimer clock;
Button button(9);
TimeSpan ts;
bool colonOn;

void setup() {
    Serial.begin(9600);
    display.begin();
    display.clear();
    timer.start(500);
    
    #ifdef COUNTDOWN
        TimeSpan ts;
        ts.minutes = 15;
        uint32_t millis = ts.toMillis();
        clock.start(ts.toMillis());
    #else
        clock.start();
    #endif
}

void loop(){
    if(timer.countdownComplete()){
        
        #ifdef COUNTDOWN
            clock.timeRemaining(ts);
            bool leadingZeros = false;
        #else
            clock.timeElapsed(ts);
            bool leadingZeros = true;
        #endif
        
        #ifdef HOURS_MINUTES
            display.writeTime(ts.hours, ts.minutes, colonOn, leadingZeros);
        #else
            display.writeTime(ts.minutes, ts.seconds, colonOn, leadingZeros);
        #endif
        
        colonOn = !colonOn;
        
        timer.reset();
    }
    
    //press button to reset clock
    while(button.Pressed()){ clock.reset(); }
}

