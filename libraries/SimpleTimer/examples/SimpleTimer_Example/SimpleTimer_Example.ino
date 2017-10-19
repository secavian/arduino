#include <SimpleTimer.h>

SimpleTimer timerElapsed;
SimpleTimer timerRemaining;
SimpleTimer timerWait;

void setup(){
    Serial.begin(9600);
    timerRemaining.start(5000);
    timerElapsed.start();
}

void loop(){
    timerWait.start();
    
    Serial.print("Time Elapsed: "); Serial.println(timerElapsed.elapsed());
    Serial.print("Time Remaining: "); Serial.println(timerRemaining.remaining());
    Serial.println("-");
    
    //delay between 5ms to 15ms);
    delay(random(5, 15));
    
    timerWait.wait(500);
}

