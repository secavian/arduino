#include <RGBLed.h>

/*********************

Demonstrate how to control a 3 color LED using this library

Connect ground terminal of LED to GND
Connect 330K Ohm Resistor (R1) between the Red terminal of LED and digital pin 11 (PWM)
Connect 330K Ohm Resistor (R2) between the GREEN terminal of LED and digital pin 10 (PWM)
Connect 330K Ohm Resistor (R3) between the BLUE terminal of LED and digital pin 9 (PWM)

               _______
              | <LED> |
              | RED   |-----[ R1 ]----------> Digital Pin 11
 GND >--------| GND   |
              | GREEN |-----[ R2 ]----------> Digital Pin 10
              |_BLUE__|-----[ R3 ]----------> Digital Pin 9
    
    Where:
        R1      = 330 Ohm Resistor
        R2      = 330 Ohm Resistor
        R3      = 330 Ohm Resistor
        <LED>   = 3 color LED
*********************/

//define the pins used in this sketch
#define RED_LED     11
#define GREEN_LED   10
#define BLUE_LED    9        

//define colors
#define BLUE    0,0,255
#define GREEN   0,255,0
#define AQUA    0,255,255
#define RED     255,0,0
#define PURPLE  255,0,255
#define YELLOW  255,255,0
#define WHITE   255,255,255
#define OTHER   0xCD,0x5C,0xFC  //just some random values

//define intensity levels
#define IFULL   0xFF
#define IHIGH   0xA0
#define IMED    0x50
#define ILOW    0x10
#define IDIM    0x03

//how long does the sketch pause each time a color is set?
#define DELAY   500

//this is the RGB LED being controlled
//there's no need to set pin modes using this class
//as that is handled automatically
RGBLed rgbled(RED_LED, GREEN_LED, BLUE_LED);

//this is the intensity of the LEDs for each loop
//LED pins *must* be PWM (~) for this to work
uint8_t intensity = IDIM;

//place holder
void setup() {
}

void loop() {
    //cycle through the predefine colors
    rgbled.Intensity(intensity);
    
    rgbled.On(RED);    delay(DELAY);
    rgbled.On(GREEN);  delay(DELAY);
    rgbled.On(BLUE);   delay(DELAY);
    rgbled.On(YELLOW); delay(DELAY);  
    rgbled.On(PURPLE); delay(DELAY);
    rgbled.On(AQUA);   delay(DELAY);
    rgbled.On(OTHER);  delay(DELAY);
    rgbled.On(WHITE);  delay(DELAY);
    
    //turn the colors off
    rgbled.Off();                delay(DELAY);
    
    //change the intensity level of the next pass through 
    //this loop function
    toggleIntensity();
}

void toggleIntensity(){
    //increase intensity from lower to higher. if the intensity
    //level is maxed out, then start over
    
    if(intensity == IFULL){
        intensity = IDIM;
    }
    else if(intensity == IDIM){
        intensity = ILOW;
    }
    else if(intensity == ILOW){
        intensity = IMED;
    }
    else if(intensity == IMED){
        intensity = IHIGH;
    }
    else { intensity = IFULL; }
}
