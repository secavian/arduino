/*
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
*/
#ifndef _SERIAL_7_SEGMENT_H_
#define _SERIAL_7_SEGMENT_H_

#if (ARDUINO >= 100)
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <I2CLib.h>

#define SERIAL_7_DEFAULT_ADDRESS                0x71

#define SERIAL_7_CLEAR_COMMAND                  0x76
#define SERIAL_7_DECIMAL_CONTROL_COMMAND        0x77
#define SERIAL_7_CURSOR_COMMAND                 0x79
#define SERIAL_7_BRIGHTNESS_COMMAND             0x7A
#define SERIAL_7_DIGIT_1_COMMAND                0x7B
#define SERIAL_7_DIGIT_2_COMMAND                0x7C
#define SERIAL_7_DIGIT_3_COMMAND                0x7D
#define SERIAL_7_DIGIT_4_COMMAND                0x7E
#define SERIAL_7_BAUD_RATE_COMMAND              0X7F
#define SERIAL_7_I2C_ADDRESS_COMMAND            0X80
#define SERIAL_7_FACTORY_RESET                  0X91

#define SERIAL_7_DECIMAL_CONTROL_APOSTROPHE     0x20
#define SERIAL_7_DECIMAL_CONTROL_COLON          0x10
#define SERIAL_7_DECIMAL_CONTROL_DIGIT_4        0x08
#define SERIAL_7_DECIMAL_CONTROL_DIGIT_3        0x04
#define SERIAL_7_DECIMAL_CONTROL_DIGIT_2        0x02
#define SERIAL_7_DECIMAL_CONTROL_DIGIT_1        0x01

#define SERIAL_7_CURSOR_4                       0x00
#define SERIAL_7_CURSOR_3                       0x01
#define SERIAL_7_CURSOR_2                       0x02
#define SERIAL_7_CURSOR_1                       0x03

#define SERIAL_7_DIGIT_SEGMENT_TOP              0x01
#define SERIAL_7_DIGIT_SEGMENT_TOP_RIGHT        0x02
#define SERIAL_7_DIGIT_SEGMENT_BOTTOM_RIGHT     0x04
#define SERIAL_7_DIGIT_SEGMENT_BOTTOM           0x08
#define SERIAL_7_DIGIT_SEGMENT_BOTTOM_LEFT      0x10
#define SERIAL_7_DIGIT_SEGMENT_TOP_LEFT         0x20
#define SERIAL_7_DIGIT_SEGMENT_MIDDLE           0x40

//I2CLib derived class for interacting with sensor.
class Serial7Segment : public I2CLib{
public:
    /* constructors */
    Serial7Segment() : I2CLib(SERIAL_7_DEFAULT_ADDRESS){}
    Serial7Segment(uint8_t address) : I2CLib(address){}
    
    /* initialize I2C bus */
    void begin(void);
    
    /* clear the display */
    void clear(void);
    
    /* update display of apostrophe, colon and decimal points */
    void decimalControl(uint8_t bitmask);
    
    /* set cursor for write */
    void setCursor(uint8_t cursorPostion);
    
    /* set brightness */
    void setBrightness(uint8_t brightness);
    
    /* turn individual segments of led's on or off */
    void setDigitSegments(uint8_t digit, uint8_t segments);
    
    /* restore factory setttings (I2C Address and Baud) */
    void factoryReset(void);
    
    /* output string values to display */
    void printString(String value);
    
    /* output time values such as 1:00 or 01:00 */
    void writeTime(uint8_t t1, uint8_t t2, bool colonOn, bool leadingZerosT1);
    
    /* output byte as hex */
    void writeHex(uint8_t value);
    void writeHex(uint16_t value);
    
    /* output float value */
    void writeFloat(float value, uint8_t precision, char buffer[]);
    void parseFloat(float value, uint8_t precision, int16_t &intPart, uint16_t &fracPart);
};

#endif
