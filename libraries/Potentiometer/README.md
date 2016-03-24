SecAviTools Potentiometer Arduino Library
========================================

This archive contains an Arduino library and example sketches showing how to use this library. The library must be installed onto your computer in order for the example code to work correctly.

This library is part of a set of libraries released on https://github.com/secavian/arduino/tree/master/libraries

This library simplifes using Potentiometer in code.

Sample Usage
-------------------
    #include <Potentiometer.h>
    #include <Led.h>
    
    Led led(10);
    Potentiometer pot(A0);
    
    void setup(){}
    
    void loop(){
        int16_t value = pot.Value(true);
        uint8_t scaledValue = (uint8_t)map(value, 0, 1023, 0, 255);
        led.On(scaledValue);
    }

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

This product is open source

Please use, reuse, and modify these files as you see fit. Please release anything derivative under the same license.

Distributed as-is; no warranty is given.
