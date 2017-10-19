#include <Led.h>
#include <XBee2.h>
#include <SoftwareSerial.h>

Led led(LED_BUILTIN);

//uncomment to use software serial instead of hardware serial
SoftwareSerial Serial1(2, 3);

uint8_t payload[5] { 0x54, 0x45, 0x53, 0x53, 0x0D };
TxRequest tx(&Serial1);
uint8_t frameId = 0;

void setup(){
    Serial.begin(115200);
    Serial1.begin(115200);
}

void loop(){
    led.Toggle();
    
    tx.Write(payload, sizeof(payload), frameId++);
    delay(1000);
}
