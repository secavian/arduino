#include "SimpleTimer.h"

void SimpleTimer::start(){
    _startTicks = millis();
}
    
void SimpleTimer::start(uint32_t millis){
    start();
    _countDown = millis;
}

uint32_t SimpleTimer::elapsed(){
    return millis() - _startTicks;
}

uint32_t SimpleTimer::remaining(){
    uint32_t m = millis();
    
    if((m - _startTicks) > _countDown){ return 0; }
    return _countDown - m;
}

void SimpleTimer::wait(uint32_t waitTicks){
    while((millis() - _startTicks) < waitTicks){}
}
