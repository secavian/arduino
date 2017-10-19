#include <Led.h>

Led led(13);

#include <SoftwareSerial.h>
SoftwareSerial GPS_SERIAL(2, 3);
//#define GPS_SERIAL  Serial1
//#define GPS_SERIAL  Serial2
//#define GPS_SERIAL  Serial3

void setup() {
    Serial.begin(115200);
    GPS_SERIAL.begin(9600);
}

void loop(){
    while(GPS_SERIAL.available()){
        Serial.print((char)GPS_SERIAL.read());
    }
    delay(50);
    led.Toggle();
}

