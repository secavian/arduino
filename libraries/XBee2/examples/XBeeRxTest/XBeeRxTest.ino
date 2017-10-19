#include <Led.h>
#include <XBee2.h>

#include <SoftwareSerial.h>
SoftwareSerial Serial1(2,3);

Led led(LED_BUILTIN);

RxPacket rx(&Serial1);

void setup(){
    Serial.begin(9600);
    
    //make sure there is a source sending data and match the baud rates.
    //don't ask how i know this, just take my word for it
    Serial1.begin(115200);
}

void loop(){
    uint8_t r = rx.Read();
    switch(r){
        case API_RXPACKET_READ_SUCCESS:
            led.Toggle();

            Serial.print("\nOK ");
            for(uint8_t i = 0; i < rx.PayloadLength; i++){
                uint8_t b = rx.Payload[i];
                
                if(b < 0x10){ Serial.print("0"); }
                Serial.print(b, HEX);
                Serial.print(" ");
            }
            Serial.println();
            break;
            
        case API_RXPACKET_READ_ERROR:
            led.Toggle();

            Serial.print("\nERR: ERR CODE: 0x");
            Serial.println(r, HEX);
            break;
    }
    
    //do other work while waiting on new data
    Serial.print(".");
    delay(25);
}

