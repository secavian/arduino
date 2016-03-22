#ifndef _POTENTIOMETER_H_
#define _POTENTIOMETER_H_

#if defined(ARDUINO) && ARDUINO >= 100
    #include "arduino.h"
#else
    #include "WProgram.h"
#endif

class RGBLed{
public:
    RGBLed(uint8_t redPin, uint8_t greenPin, uint8_t bluePin);
    RGBLed(uint8_t redPin, uint8_t greenPin, uint8_t bluePin, bool commonAnode);
    void On(uint8_t red, uint8_t green, uint8_t blue);
    void On(uint8_t red, uint8_t green, uint8_t blue, uint8_t intensity);
    void Off();
    
    bool CommonAnode(){ return _commonAnode; }
    void CommonAnode(bool value){ _commonAnode = value; }
    
    uint8_t Intensity(){ return _intensity; }
    void Intensity(uint8_t value){ _intensity = value; }
    
    uint8_t Red(){ return _red; }
    uint8_t Green(){ return _green; }
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