Bosch BNO055 IMU Sensor Library
------------------------------------------------------

Library for asynchronouse use of BNO055 Sensor

Inherits from I2CLib class. That library must be installed.

------------------------------------------------------------

This library allows for asynchronous use of the sensor. The sensor requires a
delay of 25ms between reads. This may or may not be an issue depending on the purpose
this sensor is being used for. Importantly, this is magnified if one or more long
running devices are used at the same time as this sensor. The cummulative delays
can add up and become greater than is desirable. This library along with others in
the set attempts to address that issue.

The calling process starts by calling into the read() method. This library
initiates a fresh read then immediately returns to the calling process. Each
subsequent call into the read() method causes the library to resume where it
last left off. A return value is passed back to the caller to indicate the state
of the machine (reading, success or error).

This is a highly simplifed library. It only supports reading euler values for NDOF
mode.

READING:    A fresh read has been started and the library is waiting to ensure
            at least 25ms have elapsed since the previous read.

SUCCESS:    A read has been successfully completed and values have been updated.

ERROR:      A unexpected error occurred. The library has abandoned the current
            read operation and is ready to start a new read. The values have
            not be updated.


SAMPLE USAGE:
-------------------

```cpp

#include <Led.h>
#include <BNO055.h>

Led redLed(5);
Led systemLed(13);

BNO055 bno;

void setup() {
    Serial.begin(115200);
    delay(1000);
    
    Serial.println("begin imu");
    if(bno.begin(IMU_OPERATION_MODE_NDOF) != IMU_ERROR_NONE){
        redLed.On();
        while(true){
            Serial.print("IMU ERROR: ");
            Serial.println(bno.errorCode);
            delay(1000);
        }
    }
}

void loop(){
    uint8_t r = bno.read();
    
    //if '*' displayed, then sensor read. otherwise, using unchanged values
    Serial.print(r == IMU_STATUS_SUCCESS ? "*" : " ");
    Serial.print("\theading: ");Serial.print(bno.heading);
    Serial.print("\tpitch:   ");Serial.print(bno.pitch);
    Serial.print("\troll:    ");Serial.print(bno.roll);
    Serial.println();
    
    if(r == IMU_STATUS_SUCCESS){
        systemLed.Toggle();
    }
    
    delay(5);
}

```

Repository Contents
-------------------------
* **/examples** - Example sketches for the library (.ino). Run these from the Arduino IDE. 
* **/src** - Source files for the library (.cpp, .h).
* **keywords.txt** - Keywords from this library that will be highlighted in the Arduino IDE. 
* **library.properties** - General library properties for the Arduino package manager. 
* **LICENSE.md** - Licence information.
* **README.md** - This file.

================================================================================

##Version History

* V_1.0.0 - Initial Release

================================================================================

##License Information

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

    **************************************************************************
    This is a library for the BNO055 orientation sensor

    Designed specifically to work with the Adafruit BNO055 Breakout.

    Pick one up today in the adafruit shop!
    ------> http://www.adafruit.com/products

    These sensors use I2C to communicate, 2 pins are required to interface.

    Adafruit invests time and resources providing this open source code,
    please support Adafruit andopen-source hardware by purchasing products
    from Adafruit!

    Written by KTOWN for Adafruit Industries.

    MIT license, all text above must be included in any redistribution
    **************************************************************************
