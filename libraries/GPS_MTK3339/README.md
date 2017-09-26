Adafruit Ultimate GPS Sensor Library
---------------------------------------

Library for asynchronouse use of Adafruit Ulitmate GPS
(MTK3339 Version 3)

---------------------------------------

This library allows for asynchronous use of the sensor. Data from the sensor
is typically generated every second or so. This library checks to see if the sensor
has fresh data available to read and immediately returns if not.  Once data is
available, it is read and parsed. Only NMEA GGA and RMC sentence types are
supported at this time. All other sentence types are ignored.

The calling process starts by calling into the Read() method. This library
initiates a fresh read then immediately returns to the calling process if no
data is available. Each subsequent call into the read() method causes the library
to resume where it last left off. A return value is passed back to the caller to
indicate the state of the machine (reading, success or error).

GPS_STATUS_NODATA:          GPS reports no new data available to parse.

GPS_STATUS_READING:         A read is in progress.

GPS_STATUS_SUCCESS_GGA:     A read has been successfully completed and values have
GPS_STATUS_SUCCESS_RMC:     been processed. The status code reflects the sentence
                            type that was processed on this read.

GPS_STATUS_SUCCESS_OTH:     A read has been successfully completed but the sentence
                            type is not supported.

GPS_ERROR_CHECKSUM:         A unexpected error occurred. The library has abandoned 
GPS_ERROR_PARSE_ERR:        the current read operation and is ready to start a new
GPS_ERROR_TIMEOUT:          read. The values have not be updated.

SAMPLE USAGE:
---------------------------------------

```cpp

#include <GPS_MTK3339.h>
#include <SoftwareSerial.h>

SoftwareSerial Serial1(2, 3);
GPS_MTK3339 gps(&Serial1);

void setup() {
    Serial.begin(115200);
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

```

Repository Contents
---------------------------------------

* **/examples** - Example sketches for the library (.ino). Run these from the Arduino IDE. 
* **/src** - Source files for the library (.cpp, .h).
* **keywords.txt** - Keywords from this library that will be highlighted in the Arduino IDE. 
* **library.properties** - General library properties for the Arduino package manager. 
* **LICENSE.md** - Licence information.
* **README.md** - This file.

Version History
---------------------------------------

* V_1.0.0 - Initial Release

License Information
---------------------------------------

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

This library draws heavily on the work by the folks at adafruit.
The original license text of that work follows:

    // **************************************************************************
    //  This is a library for the BNO055 orientation sensor
    //
    //  Designed specifically to work with the Adafruit BNO055 Breakout.
    //
    //  Pick one up today in the adafruit shop!
    //  ------> http://www.adafruit.com/products
    //
    //  These sensors use I2C to communicate, 2 pins are required to interface.
    //
    //  Adafruit invests time and resources providing this open source code,
    //  please support Adafruit andopen-source hardware by purchasing products
    //  from Adafruit!
    //
    //  Written by KTOWN for Adafruit Industries.
    //
    //  MIT license, all text above must be included in any redistribution
    // **************************************************************************
