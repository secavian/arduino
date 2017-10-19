#include <AfroEsc30ALib.h>

void ESCLib::arm(uint16_t armDelay){
    attach(_pin);
    writeMicroseconds(armDelay);
}

void ESCLib::setThrottle(uint16_t value){
    if(value > _pwmMax){ value = _pwmMax; }
    else if(value < _pwmMin){ value = _pwmMin; }
    
    writeMicroseconds(value);
}

void ESCLib::off(){
    writeMicroseconds(_pwmMin - 10);
}


