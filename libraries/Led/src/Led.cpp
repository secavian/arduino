#include "Led.h"

Led::Led(uint8_t pin) : _pin(pin), _state(LOW) {
    pinMode(pin, OUTPUT);
}

Led::Led(uint8_t pin, bool on) : _pin(pin), _state(LOW) {
    pinMode(pin, OUTPUT);
    if(on){ On(); } else { Off(); }
}

void Led::On(void) {
    _state = HIGH;
    digitalWrite(_pin, _state);
    
    _blinking = false;
}

void Led::On(uint8_t intensity) {
    double intens = (double)intensity / 255.0;
    
    _state = (uint8_t)(255.0 * intens);
    analogWrite(_pin, _state);
    
    _blinking = false;
}

void Led::OnWhen(bool on) {
    if (on) On();
    else Off();
}

void Led::OnWhen(bool on, uint8_t intensity) {
    if (on) On(intensity);
    else Off();
}

void Led::OnIf(bool on) {
    if (on) On();
}

void Led::OnIf(bool on, uint8_t intensity) {
    if (on) On(intensity);
}

void Led::OffIf(bool off) {
    if (off) Off();
}

void Led::Off(void) {
    _state = LOW;
    digitalWrite(_pin, _state);
    
    _blinking = false;
}

void Led::Toggle() {
    if (_state == LOW) On();
    else Off();
    
    _blinking = false;
}

bool Led::IsOn(){
    return _state == HIGH;
}

void Led::ToggleWhen(bool toggle) {
    if (toggle) { Toggle(); }
}

void Led::Blink(uint16_t rate){
    if(_blinking == false){ 
        _blinking = true;
        _blinkStart = millis();
        _blinkRate = rate;
    }
    
    if((millis() - _blinkStart) >= _blinkRate) {
        Toggle();
        _blinkStart = millis();
    }
}

uint8_t Led::Pin() { return _pin; }

uint8_t Led::State() { return _state; }
