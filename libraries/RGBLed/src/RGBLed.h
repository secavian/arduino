#ifndef _POTENTIOMETER_H_
#define _POTENTIOMETER_H_

#if defined(ARDUINO) && ARDUINO >= 100
    #include "arduino.h"
#else
    #include "WProgram.h"
#endif

class RGBLed{
public:
    //initializes new instance of RGBLed class with specified pins
    RGBLed(uint8_t redPin, uint8_t greenPin, uint8_t bluePin);
    
    //initializes new instance of RGBLed class with specified pins and common anode flag
    RGBLed(uint8_t redPin, uint8_t greenPin, uint8_t bluePin, bool commonAnode);
    
    //adjusts the red/green/blue LEDs at the current intensity
    void On(uint8_t red, uint8_t green, uint8_t blue);
    
    //adjusst the red/green/blue LEDs at the specified intensity
    void On(uint8_t red, uint8_t green, uint8_t blue, uint8_t intensity);
    
    //turns off the LEDs
    void Off();
    
    //gets/sets the common anode flag
    bool CommonAnode(){ return _commonAnode; }
    void CommonAnode(bool value){ _commonAnode = value; }
    
    //gets/sets the intensity of the LEDs
    uint8_t Intensity(){ return _intensity; }
    void Intensity(uint8_t value){ _intensity = value; }
    
    //gets the value of the red LED
    uint8_t Red(){ return _red; }
    
    //gets the value of the green LED
    uint8_t Green(){ return _green; }
    
    //gets the value of the blue LED
    uint8_t Blue(){ return _blue; }
private:
    uint8_t _redPin;
    uint8_t _greenPin;
    uint8_t _bluePin;
    uint8_t _red = 0x00;
    uint8_t _green = 0x00;
    uint8_t _blue = 0x00;
    uint8_t _intensity = 0xFF;
    bool    _commonAnode = false;
    
    void setColor();
};

#endif