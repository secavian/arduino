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
    
    This library draws heavily on the work by Mike Grusin of Sparkfun Electronics.
    The original license text of that work follows:
    
        SFE_BMP180.h
        Bosch BMP180 pressure sensor library for the Arduino microcontroller
        Mike Grusin, SparkFun Electronics

        Uses floating-point equations from the Weather Station Data Logger project
        http://wmrx00.sourceforge.net/
        http://wmrx00.sourceforge.net/Arduino/BMP085-Calcs.pdf

        Forked from BMP085 library by M.Grusin

        version 1.0 2013/09/20 initial version
        Verison 1.1.2 - Updated for Arduino 1.6.4 5/2015
        
        Our example code uses the "beerware" license. You can do anything
        you like with this code. No really, anything. If you find it useful,
        buy me a (root) beer someday.
    
    ================================================================================
    
    Library for asynchronouse use of Bosch BMP180 sensor
    
    Inherits from I2CLib class. That library must be installed.
    
    ================================================================================
    
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
    
    ================================================================================
    
    SAMPLE USAGE:
    
    #include <BMP180.h>
    BMP180 bmp;
    
    void setup(){
        Serial.begin(9600);
        bmp.begin(BMP180_STANDARD_RESOLUTION);
    }
    
    void loop(){
        if(bmp.read() == BMP_STATUS_SUCCESS) Serial.println("Read complete");
    }
    ================================================================================
*/
#ifndef _BMP180_H_
#define _BMP180_H_

#if (ARDUINO >= 100)
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <I2CLib.h>

//result of most recent read request
static const uint8_t BMP_STATUS_SUCCESS             = 0;
static const uint8_t BMP_STATUS_READING             = 1;
static const uint8_t BMP_STATUS_ERROR               = 2;

//available resolutions. defaults to 0 if not supplied or out of range
static const uint8_t BMP180_ULTRA_LOW_POWER         = 0;
static const uint8_t BMP180_STANDARD_RESOLUTION     = 1;
static const uint8_t BMP180_HIGH_RESOLUTION         = 2;
static const uint8_t BMP180_ULTRA_HIGH_RES          = 3;

//=======================================================
//INTERNAL USE
//addresses, registers and commands
static const uint8_t BMP180_ADDRESS                 = 0x77;
static const uint8_t BMP180_REG_CONTROL             = 0xF4;
static const uint8_t BMP180_REG_RESULT              = 0xF6;
static const uint8_t BMP180_CMD_TEMPERATURE         = 0x2E;
static const uint8_t BMP180_CMD_PRESSURE            = 0x34;
static const uint8_t BMP180_COMMAND_LOW_POWER_MODE  = 0x34;    //resolution == 0
static const uint8_t BMP180_COMMAND_STD_MODE        = 0x74;    //resolution == 1
static const uint8_t BMP180_COMMAND_HI_RES_MODE     = 0xB4;    //resolution == 2
static const uint8_t BMP180_COMMAND_ULT_HI_RES_MODE = 0xF4;    //resolution == 3

//state machine steps
static const int BMP_STEP_START_TEMP                = 0;
static const int BMP_STEP_WAIT_TEMP                 = 1;
static const int BMP_STEP_START_PRESS               = 2;
static const int BMP_STEP_WAIT_PRESS                = 3;
static const int BMP_STEP_READ_VALUES               = 4;
//=======================================================



//I2CLib derived class for interacting with sensor.
class BMP180 : I2CLib{
public:
    /*  constructor */
    BMP180() : I2CLib(BMP180_ADDRESS){}
    
    /*  initializes the I2C bus
        -------------------------------------------------------
        parameters:
        -------------------------------------------------------
        resolution  uint8_t     defines the resolution of the
                                device. Must be between 0 and 3.
                                Defaults to 0 (low power) if an
                                invalid value is passed in or if
                                the overloaded parameterless
                                method is called.
        -------------------------------------------------------
        return value:
            true if the sensor could be read
            false otherwise (check the wiring in this case)
        -------------------------------------------------------
    */
    bool begin(void);
    bool begin(uint8_t resolution);
    
    /*  initiates or continues a read. this is a multi step (state) operation
        
        1.  start read temperature.         returns BMP_STATUS_READING
            moves to next state
        
        2.  check to see if delay has       returns BMP_STATUS_READING
            expired (min 5ms). if not,
            remains in this state.
            otherwise, moves to next
            state
            
        3.  start read pressure.            returns BMP_STATUS_READING
            moves to next state
        
        4.  check to see if delay has       returns BMP_STATUS_READING
            expired (min 5ms for low
            power read, min 26ms for
            ultra high mode). if not,
            remains in this state.
            otherwise, moves to next
            state
            
        3.  calculates values.              returns BMP_STATUS_SUCCESS
            resets for a new read.
        -------------------------------------------------------
        return value:
            BMP_STATUS_READING while waiting for read to complete.
            BMP_STATUS_SUCCESS once read has completed.
            BMP_STATUS_ERROR otherwise.
        -------------------------------------------------------
    */
    uint8_t read(void);

    /*  values read from sensor */
    float tempC;
    float tempF;
    float pressPa;
    float pressMb;
    float pressInHg;
private:
    //low power through ultra high reslution
    uint8_t oversampling = 0;
    
    //sets the resolution
    void setOversample(uint8_t value);
    
    //individual steps of the state machine.
    uint8_t startTemperature();
    uint8_t waitTemperature();
    uint8_t startPressure();
    uint8_t waitPressure();
    uint8_t readCompensatedValues();
    
    //machine state tracking
    uint8_t currentStep;
    uint32_t currentTicks;
    uint32_t delayTicks;
    
    //variables needed for calcuations. thanks for the hard work, mike.
    int32_t AC1, AC2, AC3, VB1, VB2, B5, B6Sq, MB, MC, MD;
    uint32_t AC4, AC5, AC6, B4, B7;
    float uncompTemp, uncompPress, compTemp;
    float c5,c6,mc,md,x0,x1,x2,y0,y1,y2,p0,p1,p2;
};

#endif
