#include <Led.h>

Led led(LED_BUILTIN);

void setup(){ }

void loop(){
    led.Blink(25);
}