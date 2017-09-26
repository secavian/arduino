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
    
    This library draws heavily on the work by the folks at adafruit.
    The original license text of that work follows:
    
        // **************************************************************************
        //  This is a library for the BNO055 orientation sensor
        //
        //  Designed specifically to work with the Adafruit BNO055 Breakout.
        //
        //  Pick one up today in the adafruit shop!
        //  ------> http://www.adafruit.com/products
        //
        //  These sensors use I2C to communicate, 2 pins are required to interface.
        //
        //  Adafruit invests time and resources providing this open source code,
        //  please support Adafruit andopen-source hardware by purchasing products
        //  from Adafruit!
        //
        //  Written by KTOWN for Adafruit Industries.
        //
        //  MIT license, all text above must be included in any redistribution
        // **************************************************************************
    
    ================================================================================
    
    Library for asynchronouse use of BNO055 Sensor
    
    Inherits from I2CLib class. That library must be installed.
    
    ================================================================================
    
    This library allows for asynchronous use of the sensor. The sensor requires a
    delay of 25ms between reads. This may or may not be an issue depending on the purpose
    this sensor is being used for. Importantly, this is magnified if one or more long
    running devices are used at the same time as this sensor. The cummulative delays
    can add up and become greater than is desirable. This library along with others in
    the set attempts to address that issue.
    
    The calling process starts by calling into the read() method. This library
    initiates a fresh read then immediately returns to the calling process. Each
    subsequent call into the read() method causes the library to resume where it
    last left off. A return value is passed back to the caller to indicate the state
    of the machine (reading, success or error).
    
    This is a highly simplifed library. It only support reading euler values for NDOF
    mode.
    
    READING:    A fresh read has been started and the library is waiting to ensure
                at least 25ms have elapsed since the previous read.
    
    SUCCESS:    A read has been successfully completed and values have been updated.
    
    ERROR:      A unexpected error occurred. The library has abandoned the current
                read operation and is ready to start a new read. The values have
                not be updated.
    
    ================================================================================
    
    SAMPLE USAGE:
    
    #include <BNO055.h>
    BNO055 imu;
    
    void setup(){
        Serial.begin(9600);
        imu.begin(IMU_OPERATION_MODE_NDOF);
    }
    void loop(){
        if(imu.read() == IMU_STATUS_SUCCESS) Serial.println("Read complete");
    }
    
    ================================================================================
*/

#ifndef _BNO055_H_
#define _BNO055_H_

#include "Arduino.h"
#include <I2CLib.h>

//I2C addresses
static const uint8_t BNO055_ADDRESS_DEFAULT                 = 0x28;
static const uint8_t BNO055_ADDRESS_ALTERNATE               = 0x29;

//result of most recent read request
static const uint8_t IMU_STATUS_SUCCESS                     = 0;
static const uint8_t IMU_STATUS_READING                     = 1;
static const uint8_t IMU_STATUS_ERROR                       = 2;

//error codes
static const uint8_t IMU_ERROR_NONE                         = 0x00;
static const uint8_t IMU_ERROR_READ                         = 0x01;
static const uint8_t IMU_ERROR_SET_OP_MODE                  = 0x06;
static const uint8_t IMU_ERROR_RESET_PWR_MODE_WRITE         = 0x08;

//operating modes. passed into begin() method. defaults
//to NDOF (0x0C) if not specified or out of range.
static const uint8_t IMU_OPERATION_MODE_CONFIG              = 0X00;
static const uint8_t IMU_OPERATION_MODE_ACCONLY             = 0X01;
static const uint8_t IMU_OPERATION_MODE_MAGONLY             = 0X02;
static const uint8_t IMU_OPERATION_MODE_GYRONLY             = 0X03;
static const uint8_t IMU_OPERATION_MODE_ACCMAG              = 0X04;
static const uint8_t IMU_OPERATION_MODE_ACCGYRO             = 0X05;
static const uint8_t IMU_OPERATION_MODE_MAGGYRO             = 0X06;
static const uint8_t IMU_OPERATION_MODE_AMG                 = 0X07;
static const uint8_t IMU_OPERATION_MODE_IMUPLUS             = 0X08;
static const uint8_t IMU_OPERATION_MODE_COMPASS             = 0X09;
static const uint8_t IMU_OPERATION_MODE_M4G                 = 0X0A;
static const uint8_t IMU_OPERATION_MODE_NDOF_FMC_OFF        = 0X0B;
static const uint8_t IMU_OPERATION_MODE_NDOF                = 0X0C;

//=======================================================
//INTERNAL USE
// Euler data registers 
static const uint8_t BNO055_EULER_VALUES_ADDR               = 0X1A;

// Mode registers 
static const uint8_t BNO055_OPR_MODE_ADDR                   = 0X3D;
static const uint8_t BNO055_PWR_MODE_ADDR                   = 0X3E;

//power modes
static const uint8_t BNO055_POWER_MODE_NORMAL               = 0X00;
static const uint8_t BNO055_POWER_MODE_LOWPOWER             = 0X01;
static const uint8_t BNO055_POWER_MODE_SUSPEND              = 0X02;
//=======================================================



//I2CLib derived class for interacting with sensor.
class BNO055 : I2CLib{
public:
    /*  constructor */
    BNO055() : BNO055(BNO055_ADDRESS_DEFAULT){}
    BNO055(uint8_t address) : I2CLib(address){}
    
    /*  initializes the I2C bus
        -------------------------------------------------------
        parameters:
        -------------------------------------------------------
        operatingMode  uint8_t  the operating mode for the sensor.
                                currently only support ndof mode.
        -------------------------------------------------------
        return value:
            true if the sensor could be read
            false otherwise (check the wiring in this case)
        -------------------------------------------------------
    */
    uint8_t begin(void);
    uint8_t begin(uint8_t operatingMode);
    
    /*  initiates or continues a read. this is a multi step (state) operation
        
        1.  verify sufficient ticks have    returns IMU_STATUS_READING
            elapsed between reads. returns
            if successive reads are too
            quickly spaced.
        
        2.  read the current values.        returns IMU_STATUS_SUCCESS
            sets the most recent read
            ticks.
        -------------------------------------------------------
        return value:
            READING while waiting for read to complete.
            SUCCESS once read has completed.
            ERROR otherwise.
        -------------------------------------------------------
    */
    uint8_t read(void);
    
    /*  set when methods return other than IMU_STATUS_ERROR */
    uint8_t errorCode;
    
    /*  values read from sensor */
    float heading;
    float pitch;
    float roll;
private:
    uint8_t _data[6];
    
    uint32_t _lastReadTicks;
    uint8_t setOperatingMode(uint8_t mode);
    uint8_t _mode;
};
#endif
