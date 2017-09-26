#include <GPS_MTK3339.h>

#include <SoftwareSerial.h>
SoftwareSerial Serial1(2, 3);

GPS_MTK3339 gps(&Serial1);

void setup() {
    Serial.begin(9600);
    Serial1.begin(9600);
}

void loop(){
    uint8_t r = gps.Read();
    bool r2 = false;
    
    switch(r){
        case GPS_STATUS_SUCCESS_GGA:
            Serial.println("  GGA:");
            r2 = true;
            break;
        case GPS_STATUS_SUCCESS_RMC:
            Serial.println("  RMC:");
            r2 = true;
            break;
        case GPS_STATUS_SUCCESS_OTH:
            Serial.println("  Other sentence type read:");
            break;
    }
    
    if(r2){
        Serial.print("\tSTATUS:    ");Serial.println(gps.StatusChar);
        Serial.print("\tLATITUDE:  ");Serial.println(gps.Latitude, 2);
        Serial.print("\tLONGITUDE: ");Serial.println(gps.Longitude, 2);
        Serial.print("\tALTITUDE:  ");Serial.println(gps.Altitude, 2);
        Serial.println();
    }
    
    Serial.print(".");
    delay(50);
}

