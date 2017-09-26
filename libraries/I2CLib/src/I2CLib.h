/*
    I2C Bus Library.
    
    Allows for simplified use of the Wire.h (TwoWire) class. Used by other
    libraries in order to maintain coding consistency.
    
    Can be instantiated as an object or can be inherited from if preferred.
    
    ================================================================================
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
    ================================================================================
*/
#ifndef _I2CLIB_H_
#define _I2CLIB_H_

#include <Wire.h>

//Base class for I2C connectivity. can be instatiated as is or used as a base class
class I2CLib{
public:
    /*  constructor
        -------------------------------------------------------
        parameters:
        -------------------------------------------------------
        address     uint8_t     the I2C bus address for the
                                being accessed.
        -------------------------------------------------------
    */
    I2CLib(uint8_t address) : deviceAddress(address) {}
    
    /*  initializes the I2C bus */
    void begin(void);
    
    /*  reads a signed or unsigned 8, 16 or 32 bit value from 
        the device
        -------------------------------------------------------
        parameters:
        -------------------------------------------------------
        address     uint8_t     the byte sent to the device
                                to signal that a read is being
                                requested. this can be a
                                register, command or other value
                                as required by the target device
                                ** THIS IS NOT THE DEVICE'S
                                   I2C BUS ADDRESS **
       
        value       int8_t      the value read from the device.
                    uint8_t
                    int16_t
                    uint16_t
                    int32_t
                    uint32_t
        -------------------------------------------------------
        return value:
            true if the read request was successful
            false otherwise
        -------------------------------------------------------
    */
    bool readInt(uint8_t address, int8_t &value);
    bool readInt(uint8_t address, uint8_t &value);
    bool readInt(uint8_t address, int16_t &value);
    bool readInt(uint8_t address, uint16_t &value);
    bool readInt(uint8_t address, int32_t &value);
    bool readInt(uint8_t address, uint32_t &value);

    /*  reads a specified number of unsigned 8 bit values
        from the device into an array
        -------------------------------------------------------
        parameters:
        -------------------------------------------------------
        address     uint8_t     the byte sent to the device
                                to signal that a read is being
                                requested. this can be a
                                register, command or other value
                                as required by the target device
                                ** THIS IS NOT THE DEVICE'S
                                   I2C BUS ADDRESS **
       
        values      uint8_t[]   buffer to store bytes returned
                                from device
       
        length      uint8_t     the number of bytes for the device
                                to return
        -------------------------------------------------------
        return value:
            true if the read request was successful
            false otherwise
        -------------------------------------------------------
    */
    bool readBytes(uint8_t address, uint8_t* values, uint8_t length);

    /*  writes a signed or unsigned 8, 16 or 32 bit value to the device
        -------------------------------------------------------
        parameters:
        -------------------------------------------------------
        address     uint8_t     the byte sent to the device
                                to signal that a write is being
                                requested. this can be a
                                register, command or other value
                                as required by the target device
                                ** THIS IS NOT THE DEVICE'S
                                   I2C BUS ADDRESS **
       
        value       uint8_t     the value being written to the device
        -------------------------------------------------------
        return value:
            true if the write request was successful
            false otherwise
        -------------------------------------------------------
    */
    bool writeInt(uint8_t address, int8_t value);
    bool writeInt(uint8_t address, uint8_t value);
    bool writeInt(uint8_t address, int16_t value);
    bool writeInt(uint8_t address, uint16_t value);
    bool writeInt(uint8_t address, int32_t value);
    bool writeInt(uint8_t address, uint32_t value);

    /*  writes a single unsigned 8 bit value to the device
        -------------------------------------------------------
        parameters:
        -------------------------------------------------------
        address     uint8_t     the byte sent to the device
                                to signal that a read is being
                                requested. this can be a
                                register, command or other value
                                as required by the target device
                                ** THIS IS NOT THE DEVICE'S
                                   I2C BUS ADDRESS **
       
        values      uint8_t[]   buffer to store values being written
                                to the device
       
        length      uint8_t     the number of bytes to write to the
                                device
        -------------------------------------------------------
        return value:
            true if the write request was successful
            false otherwise
        -------------------------------------------------------
    */
    bool writeBytes(uint8_t address, uint8_t* values, uint8_t length);
    
    /*  the I2C bus address for the device. */
    uint8_t deviceAddress;
    
protected:
    //default buffer to read values from the device.
    uint8_t _buffer[4] { 0x00, 0x00, 0x00, 0x00 };
};

#endif
