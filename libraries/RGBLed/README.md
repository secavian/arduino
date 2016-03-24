SecAviTools LED Arduino Library
========================================

This archive contains an Arduino library and example sketches showing how to use this library. The library must be installed onto your computer in order for the example code to work correctly.

This library is part of a set of libraries released on https://github.com/secavian/arduino/tree/master/libraries

This library simplifes using 3 Color LEDs in code.

Sample Usage
-------------------
    #include <RGBLed.h>
    
    #define RED_LED     11
    #define GREEN_LED   10
    #define BLUE_LED    9        
    #define BLUE    0,0,255
    #define GREEN   0,255,0
    #define AQUA    0,255,255
    #define RED     255,0,0
    #define PURPLE  255,0,255
    #define YELLOW  255,255,0
    #define WHITE   255,255,255
    #define OTHER   0xCD,0x5C,0xFC  //just some random values
    #define IFULL   0xFF
    #define IHIGH   0xA0
    #define IMED    0x50
    #define ILOW    0x10
    #define IDIM    0x03
    #define DELAY   500
    
    RGBLed rgbled(RED_LED, GREEN_LED, BLUE_LED);
    uint8_t intensity = IDIM;
    
    void setup(){}
    
    void loop(){
        rgbled.Intensity(intensity);
        
        rgbled.On(RED);    delay(DELAY);
        rgbled.On(GREEN);  delay(DELAY);
        rgbled.On(BLUE);   delay(DELAY);
        rgbled.On(YELLOW); delay(DELAY);  
        rgbled.On(PURPLE); delay(DELAY);
        rgbled.On(AQUA);   delay(DELAY);
        rgbled.On(WHITE);  delay(DELAY);
        rgbled.On(OTHER);  delay(DELAY);
        rgbled.Off();      delay(DELAY);
        
        if(intensity == IFULL){ intensity = IDIM; }
        else if(intensity == IDIM){ intensity = ILOW; }
        else if(intensity == ILOW){ intensity = IMED; }
        else if(intensity == IMED){ intensity = IHIGH; }
        else { intensity = IFULL; }
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
