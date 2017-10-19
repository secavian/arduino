Byte Converter
========================================

Allows converting between int/float types and byte arrays

Supports signed and unsigned 16, 32 and 64 bit integers
Supports float

No direct support for double

Sample Usage
-------------------

```cpp

#include <ByteConverterLib.h>

uint8_t buffer[8] {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

void setup(){
    Serial.begin(9600);
    
    float test = 123.456;
    float test2;
    
    Serial.print("value to convert: ");
    Serial.println(test, 4);
    
    clearBuffer();
    Convert.getBytes(test, buffer, 0);
    
    Serial.print("buffer values: ");
    for(uint8_t i = 0; i < sizeof(buffer); i++){
        printByte(buffer[i]);
    }
    Serial.println();
    
    test2 = Convert.getFloat(buffer, 0);
    
    Serial.print("value recovered from buffer: ");
    Serial.println(test2, 4);
}

void loop() {
}

void clearBuffer(){
    memset(buffer, 0, sizeof(buffer));
}

void printByte(uint8_t b){
    Serial.print("0x");
    if(b < 0x10) { Serial.print("0"); }
    Serial.print(b, HEX);
    Serial.print(" ");
}

```

Repository Contents
-------------------

* **/examples** - Example sketches for the library (.ino). Run these from the Arduino IDE. 
* **/src** - Source files for the library (.cpp, .h).
* **keywords.txt** - Keywords from this library that will be highlighted in the Arduino IDE. 
* **library.properties** - General library properties for the Arduino package manager. 
* **LICENSE.md** - Licence information.
* **README.md** - This file.

Version History
---------------
* V_1.0.0 - Initial Release

License Information
-------------------

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
