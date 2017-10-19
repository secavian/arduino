/*
Software License Agreement (BSD License)

Copyright (c) 2017, Ralf Thompson
All rights reserved.

Sample program to demonstate how to use this library.

Uses custom libraries for Leds and I2C connectivity. Ensure
the following libraries are installed:

I2CLib.h    I2CLib.cpp
Led.h       Led.cpp

*/

#include <Led.h>
#include <BMP180.h>

Led led(LED_BUILTIN);
BMP180 bmp180;

void setup() {
    Serial.begin(9600);
    
    //select one of the following
    //bool baroInit = bmp180.begin(); //(same as using BMP180_ULTRA_LOW_POWER)
    //bool baroInit = bmp180.begin(BMP180_ULTRA_LOW_POWER);
    //bool baroInit = bmp180.begin(BMP180_STANDARD_RESOLUTION);
    //bool baroInit = bmp180.begin(BMP180_HIGH_RESOLUTION);
    bool baroInit = bmp180.begin(BMP180_ULTRA_HIGH_RES);
    
    if( ! baroInit){
        Serial.println("ERROR INITIALIZING BMP180 SENSOR");
        while(true);
    }
}

void loop(){
    if(bmp180.read() == BMP_STATUS_SUCCESS){
        led.Toggle();
        
        Serial.println("sensor read complete.");
        Serial.print(bmp180.tempC, 1);Serial.print("C ");
        Serial.print("\t");
        Serial.print(bmp180.tempF, 1);Serial.print("F ");
        Serial.print("\t");
        Serial.print(bmp180.pressPa);Serial.print("pa ");
        Serial.print("\t");
        Serial.print(bmp180.pressMb);Serial.print("mb ");
        Serial.print("\t");
        Serial.print(bmp180.pressInHg);Serial.print("InHg");
        Serial.println();
    }
    else{
        //each of the '.' chars printed below show how other tasks can be performed while
        //waiting for sensor to finish fresh read
        
        Serial.print(".");
        //do other stuff
        
        delay(5);
    }
}

