#include "RGBLed.h"

RGBLed::RGBLed(uint8_t redPin, uint8_t greenPin, uint8_t bluePin) : 
    _redPin(redPin),
    _greenPin(greenPin),
    _bluePin(bluePin) 
{
    pinMode(_redPin, OUTPUT);
    pinMode(_greenPin, OUTPUT);
    pinMode(_bluePin, OUTPUT);
}

RGBLed::RGBLed(uint8_t redPin, uint8_t greenPin, uint8_t bluePin, bool commonAnode) :
    _redPin(redPin),
    _greenPin(greenPin),
    _bluePin(bluePin),
    _commonAnode(commonAnode)
{
    pinMode(_redPin, OUTPUT);
    pinMode(_greenPin, OUTPUT);
    pinMode(_bluePin, OUTPUT);
}

void RGBLed::On(uint8_t red, uint8_t green, uint8_t blue) { 
    _red = red;
    _green = green;
    _blue = blue;
    setColor();
}

void RGBLed::On(uint8_t red, uint8_t green, uint8_t blue, uint8_t intensity) { 
    _red = red;
    _green = green;
    _blue = blue;
    _intensity = intensity;
    setColor();
}

void RGBLed::Off(){
    _red = _green = _blue = 0;
    setColor();
}

void RGBLed::setColor(){
    double intens = (double)_intensity / (double)0xFF;
    
    uint8_t red = (int)((double)_red * intens);
    uint8_t green = (int)((double)_green * intens);
    uint8_t blue = (int)((double)_blue * intens);
    
    if(_commonAnode){
        red = 255 - red;
        green = 255 - green;
        blue = 255 - blue;
    }
    
    analogWrite(_redPin, red);
    analogWrite(_greenPin, green);
    analogWrite(_bluePin, blue);
}
