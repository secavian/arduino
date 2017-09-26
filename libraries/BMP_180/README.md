Bosch BMP180 Barometric Sensor Library
======================================

Library for asynchronouse use of Bosch BMP180 sensor

Inherits from I2CLib class. That library must be installed.

------------------

This library allows for asynchronous use of the sensor. The sensor takes a
minimum of 10ms to process a read request and can take over 30ms for high
resolution reads. This may or may not be an issue depending on the purpose
this sensor is being used for. Importantly, this is magnified if one or more long
running devices are used at the same time as this sensor. The cummulative delays
can add up and become greater than is desirable. This library along with others in
the set attempts to address that issue.

The calling process starts by calling into the read() method. This library
initiates a fresh read then immediately returns to the calling process. Each
subsequent call into the read() method causes the library to resume where it
last left off. A return value is passed back to the caller to indicate the state
of the machine (reading, success or error).

READING:    A fresh read has been started and the library is waiting for the
            sensor to complete its process before calculating pressure and
            temperature values.

SUCCESS:    A read has been successfully completed and values have been updated.

ERROR:      A unexpected error occurred. The library has abandoned the current
            read operation and is ready to start a new read. The values have
            not be updated.


SAMPLE USAGE:
------------------

```cpp

#include <BMP180.h>
BMP180 bmp;

void setup(){
    Serial.begin(9600);
    bmp.begin(BMP180_STANDARD_RESOLUTION);
}

void loop(){
    if(bmp.read() == BMP_STATUS_SUCCESS) Serial.println("Read complete");
}

```

Repository Contents
------------------

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

This library draws heavily on the work by Mike Grusin of Sparkfun Electronics.
The original license text of that work follows:

> SFE_BMP180.h
> Bosch BMP180 pressure sensor library for the Arduino microcontroller
> Mike Grusin, SparkFun Electronics
> 
> Uses floating-point equations from the Weather Station Data Logger project
> http://wmrx00.sourceforge.net/
> http://wmrx00.sourceforge.net/Arduino/BMP085-Calcs.pdf
> 
> Forked from BMP085 library by M.Grusin
> 
> version 1.0 2013/09/20 initial version
> Verison 1.1.2 - Updated for Arduino 1.6.4 5/2015
> 
> Our example code uses the "beerware" license. You can do anything
> you like with this code. No really, anything. If you find it useful,
> buy me a (root) beer someday.
