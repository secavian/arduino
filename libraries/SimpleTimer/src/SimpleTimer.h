/*
    Software License Agreement (BSD License)

    Copyright (c) 2017, Ralf Thompson
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.
    
    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
    
    ================================================================================
    
    SAMPLE USAGE:
    
    #include <SimpleTimer.h>

    SimpleTimer timerElapsed;
    SimpleTimer timerRemaining;

    void setup(){
        Serial.begin(9600);
        timerRemaining.start(5000);
        timerElapsed.start();
    }

    void loop(){
        Serial.print("Time Elapsed: "); Serial.println(timerElapsed.elapsed());
        Serial.print("Time Remaining: "); Serial.println(timerRemaining.remaining());
        Serial.println("-");
        delay(1000);
    }
    ================================================================================
*/
#ifndef _SIMPLE_TIMER_H_
#define _SIMPLE_TIMER_H_

#if defined(ARDUINO) && ARDUINO >= 100
    #include "arduino.h"
#else
    #include "WProgram.h"
#endif

class TimeSpan{
public:
    static const uint32_t millisInSeconds = 1000;
    static const uint32_t millisInMinutes = 60000;
    static const uint32_t millisInHours = 3600000;
    static const uint32_t millisInDays = 86400000;
    
    uint8_t days = 0;
    uint8_t hours = 0;
    uint8_t minutes = 0;
    uint8_t seconds = 0;
    uint16_t milliseconds = 0;
    
    void fromMillis(uint32_t millis){
        days = (millis / millisInDays);
        millis -= ((uint32_t)days * millisInDays);

        hours = (millis / millisInHours);
        millis -= ((uint32_t)hours * millisInHours);
        
        minutes = (millis / millisInMinutes);
        millis -= ((uint32_t)minutes * millisInMinutes);
        
        seconds = millis / millisInSeconds;
        milliseconds = (millis - ((uint32_t)seconds * millisInSeconds));
    }
    
    uint32_t toMillis(){
        return
            ((uint32_t)days * millisInDays) +
            ((uint32_t)hours * millisInHours) +
            ((uint32_t)minutes * millisInMinutes) +
            ((uint32_t)seconds * millisInSeconds) +
            (uint32_t)milliseconds;
    }
};

class SimpleTimer {
public:
    //initializes new timer instance
    SimpleTimer(){}
    
    //starts a stopwatch
    void start(void);
    
    //starts a countdown timer. millis is the number of milliseconds to count down from
    void start(uint32_t millis);
    
    //resets countdown counter.
    void reset(void);
    
    //millis elapsed since starting timer
    uint32_t elapsed(void);
    
    //millis remaining until countdown complete
    uint32_t remaining(void);
    
    //indicates if countdown has finished.
    bool countdownComplete(void);
    
    //waits until a number of ticks have elapsed. differs from delay(x) in that
    //delay pauses the full time. this allows a timer to start before a number
    //of other opertaions have started then pauses until after the duration has
    //completed. example:
    //
    //  SimpleTimer t;
    //  void setup(){}
    //  void loop(){
    //      t.start();
    //      doWork();
    //      t.wait(25);
    //  }
    //
    //method doWork() is some function call that takes some abritrary time to complete
    //(e.g., reading a sensor). the wait method ensures that 25ms (in this case)
    //have elapsed before initiating a new read.
    //
    //let's assume that doWork() takes, say, 5ms ~ 15ms to complete. if we use delay(25),
    //then there will be 30ms ~ 45ms between each call. using wait(25) only delays 25ms
    //regardless of the length of time that doWork() needs to complete.
    void wait(uint32_t waitTicks);
    
    void timeElapsed(TimeSpan &timespan);
    void timeRemaining(TimeSpan &timespan);

private:
    uint32_t _startTicks;
    uint32_t _countDown;
};

#endif

