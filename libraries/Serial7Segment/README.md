Sparkfun Serial Seven Segment Display
======================================

Inherits from I2CLib class. That library must be installed.

Libray to support displaying HEX, floating point and time values to 7 Segment LED display
over I2C

------------------

DESCRIBE

SAMPLE USAGE:
------------------

```cpp

#include <Serial7Segment.h>
#include <SimpleTimer.h>
#include <Button.h>

Serial7Segment display;
uint16_t counter;
SimpleTimer timer;
Button button(9);

void setup() {
    Serial.begin(9600);
    display.begin();
    display.clear();
    timer.start(10);
}

void loop(){
    if(timer.countdownComplete()){
        display.writeHex(counter++);
        timer.reset();
    }
    
    //press button to pause
    while(button.Pressed()){}
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