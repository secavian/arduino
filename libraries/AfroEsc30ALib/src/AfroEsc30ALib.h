#ifndef _AFRO_ESC_30A_LIB_h_
#define _AFRO_ESC_30A_LIB_h_

#include <Servo.h>
#include <Arduino.h>

class ESCLib : public Servo{
public:
    ESCLib(uint8_t pin, uint16_t pwmMin, uint16_t pwmMax) : Servo(), _pin(pin), _pwmMin(pwmMin), _pwmMax(pwmMax) {}
    
    void arm(uint16_t armDelay);
    
    void setThrottle(uint16_t value);
    
    void off();
    
protected:
    uint8_t _pin;
    uint16_t _pwmMin;
    uint16_t _pwmMax;
};
#endif
