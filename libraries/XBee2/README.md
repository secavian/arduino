XBEE Library
-------------------------

Library for sending/receiving API based data across XBee modules

-------------------------

This library allows is a stripped down approach to sending and receiving API
based data with an XBee module. There are two classes defined here, each representing
a different Api "Frame" - Transmit Request (Frame Type 0x10) and Receive Packet
(Frame Type 0x90). Each class contains a reference to a serial line and uses that to
send or receive data as appropriate.

Transmit Request
-------------------------

Calling processes configures the module then passes in a byte array, and length and
an optional frame id to the class. The class handles building the Api Frame and
sends it out over the serial line. This is a stricly synchronous method call

Receive Packet
-------------------------

This class allows for asynchronous use of the module during receives. The class checks
to see if the module has fresh data available to read and immediately returns if not.
Once data is available, it is parsed and the payload bytes are made available in an
array.

The calling process configures the module then calls into the Read() method. An exit
code of API_RXPACKET_NO_DATA_AVAILABLE (see the header file) is returned if no data
is available to read. Otherwise, the data is parsed. A value of API_RXPACKET_READ_SUCCESS
is returned once that is complete. If there was an error reading the data (e.g., the
checksum calculation fails), and error code is returned.

SAMPLE USAGE:
-------------------------

```cpp

#include <Led.h>
#include <XBee2.h>

//uncomment to use software serial instead of hardware serial
#include <SoftwareSerial.h>
SoftwareSerial Serial1(2,3);

Led led(LED_BUILTIN);

RxPacket rx(&Serial1);

void setup(){
    Serial.begin(9600);
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

            Serial.print("\nERR ");
            Serial.print(": ERR CODE: 0x");
            Serial.println(r, HEX);
            break;
    }
    
    //do other work while waiting on new data
    Serial.print(".");
    delay(25);
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

Version History
-------------------------

* V_1.0.0 - Initial Release

-------------------------
License Information

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
