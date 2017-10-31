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

Serial7Segment display;
uint16_t counter;
SimpleTimer timer;
Button button(9);

void setup() {
    Serial.begin(9600);
    display.begin();
    display.clear();
    timer.start(10);
}

void loop(){
    if(timer.countdownComplete()){
        display.writeHex(counter++);
        timer.reset();
    }
    
    //press button to pause
    while(button.Pressed()){}
}

