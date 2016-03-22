// ButtonSpst.h

#ifndef _BUTTON_h
#define _BUTTON_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Button {
public:
    Button(uint8_t pin);
    bool Pressed(void);
    uint8_t Pin(void);
private:
    uint8_t _pin;
};

#endif

