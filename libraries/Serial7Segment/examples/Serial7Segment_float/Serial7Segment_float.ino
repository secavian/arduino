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

#include <Button.h>
#include <Serial7Segment.h>
#include <SimpleTimer.h>

Serial7Segment display;
Button button(9);
float v = -1.0;
SimpleTimer timer;

void setup() {
    display.begin();
    display.clear();
    timer.start(200);
}

void loop(){
    if(timer.countdownComplete()){
        char tempString[10];
        display.writeFloat(v, 1, tempString);
        
        v += 0.1;
        timer.reset();
    }
    
    //press button to reset counter
    while(button.Pressed()){ v = -1.0; }
}

