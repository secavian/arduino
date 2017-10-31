#include "SimpleTimer.h"

void SimpleTimer::start(){
    _startTicks = millis();
}

void SimpleTimer::reset(){
    start();
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
    
    if((m - _startTicks) > _countDown){ 
        return 0;
    }
    return _countDown - m + _startTicks;
}

bool SimpleTimer::countdownComplete(void){
    return remaining() == 0;
}

void SimpleTimer::wait(uint32_t waitTicks){
    while((millis() - _startTicks) < waitTicks){}
}

void SimpleTimer::timeElapsed(TimeSpan &timespan){
    timespan.fromMillis(elapsed());
}

void SimpleTimer::timeRemaining(TimeSpan &timespan){
    timespan.fromMillis(remaining());
}



