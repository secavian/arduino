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

    ================================================================================
    
    Library for simplied use of XBee radio's in Api mode.
    
    ================================================================================
    
    This library allows is a stripped down approach to sending and receiving API
    based values with an XBee module. There are two classes, each representing
    a different Api "Frame" - Transmit Request (Frame Type 0x10) and Receive
    Packet (Frame Type 0x90). Each class contains a reference to a serial line and
    uses that to send or receive data as appropriate.

    ##Transmit Request

    Calling processes configures the module then passes in a byte array, and length and
    an optional frame id to the class. The class handles building the Api Frame and
    sends it out over the serial line. This is a stricly synchronous method call

    ##Receive Packet

    This class allows for asynchronous use of the module during receives. The class checks
    to see if the module has fresh data available to read and immediately returns if not.
    Once data is available, it is parsed and the payload bytes are made available in an
    array.

    The calling process configures the module then calls into the Read() method. An exit
    code of API_RXPACKET_NO_DATA_AVAILABLE (see the header file) is returned if no data
    is available to read. Otherwise, the data is parsed. A value of API_RXPACKET_READ_SUCCESS
    is returned once that is complete. If there was an error reading the data (e.g., the
    checksum calculation fails), and error code is returned.

    ================================================================================

    ##SAMPLE USAGE:

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
                Serial.print("%) ERR CODE: 0x");
                Serial.println(r, HEX);
                break;
        }
        
        //do other work while waiting on new data
        Serial.print(".");
        delay(25);
    }
    
    ================================================================================
*/
#ifndef _xbee2_h_
#define _xbee2_h_

//there's a lot going on, so off load to a separate file. all #include statements are there
#include "XBee2_defines.h"

//#define XBEE2_DEBUG
#ifdef XBEE2_DEBUG
    //#define XBEE2_TX_DEBUG
    #define XBEE2_RX_DEBUG
    #define XBEE2_DEBUG_PRINT(x) Serial.print(x);
    #define XBEE2_DEBUG_PRINTF(x,f) Serial.print(x,f);
    #define XBEE2_DEBUG_PRINTLN(x) Serial.println(x);
    #define XBEE2_DEBUG_PRINTFLN(x,f) Serial.println(x,f);
    #define XBEE2_DEBUG_PRINTBYTE(b) debugPrintByte(b);
#else
    #define XBEE2_DEBUG_PRINT(x)
    #define XBEE2_DEBUG_PRINTF(x,f)
    #define XBEE2_DEBUG_PRINTLN(x)
    #define XBEE2_DEBUG_PRINTFLN(x,f)
    #define XBEE2_DEBUG_PRINTBYTE(b)
#endif

/*  This is a half ***ed effort to build a buffer with a built in length value. It
    works, but it does consume 256 bytes of data (plus the length variable), so
    there's that. I'd change it to something else, but I have the library scattered
    about in various projects and don't wan't to bother recompiling and testing all
    of that, plus I don't want to mess with the whole memory allocate/deallocate thing
    so this is what we have.
*/
class BufferVector {
public:
    /* array contain bytes sent to or received from the module */
    byte Array[256] = { START_DELIMITER };
    
    /* the number of bytes involved in the current action */
    unsigned int Length = 0;
};

/*  Base class for Api Frame classes. Contains the serial port reference for sending
    and/or receiving data and handles talking to it as needed.
*/
class ApiFrame {
protected:
    /* Constructors - allows for support of hardware and software serial ports */
    ApiFrame(HardwareSerial * const serial) : _hserial(serial), useSoftwareSerial(false) { };
    ApiFrame(SoftwareSerial * const serial) : _sserial(serial), useSoftwareSerial(true) { };
    
    /* calculates check sum value for a byte array */
    byte calcChecksum(byte *buffer, int offset, int length){
        uint8_t b = 0;

        for(int i = 0; i < length; i++){
            b += buffer[offset + i];
        }
        
        return 0xFF - b;
    }
    
    /* writes the contents of the frame buffer to the xbee module */
    void write(void){
        if(useSoftwareSerial){
            for(uint8_t i = 0; i < Packet.Length; i++){
                _sserial->write(Packet.Array[i]);
                #ifdef XBEE2_TX_DEBUG
                    XBEE2_DEBUG_PRINTBYTE(Packet.Array[i]);
                #endif
            }
            
            _sserial->flush();
        }
        else{
            for(uint8_t i = 0; i < Packet.Length; i++){
                _hserial->write(Packet.Array[i]);
                #ifdef XBEE2_TX_DEBUG
                    XBEE2_DEBUG_PRINTBYTE(Packet.Array[i]);
                #endif
            }
            
            _hserial->flush();
        }
    }
    
    /* reads the contents of the xbee into the frame buffer */
    bool read(uint8_t &offset){
        if(useSoftwareSerial){
            if(!_sserial->available()){
                #ifdef XBEE2_RX_DEBUG
                    XBEE2_DEBUG_PRINTLN("xbee: no data available software serial");
                #endif
                return false;
            }
            while(_sserial->available()){
                Packet.Array[offset++] = _sserial->read();
            }
        }
        else{
            if(!_hserial->available()){
                #ifdef XBEE2_RX_DEBUG
                    XBEE2_DEBUG_PRINTLN("xbee: no data available hardware serial");
                #endif
                return false;
            }
            while(_hserial->available()){
                Packet.Array[offset++] = _hserial->read();
            }
        }
        return true;
    }
    
    #ifdef XBEE2_DEBUG
    void debugPrintByte(uint8_t b){
        if(b < 0x10){ Serial.print("0"); }
        Serial.print(b, HEX);
        Serial.print(" ");
    }
    #endif
    
    /* serial port to use */
    HardwareSerial *_hserial;
    SoftwareSerial *_sserial;
    bool useSoftwareSerial;
    
    /* buffer to hold data to send to or receive from the module */
    BufferVector Packet;
};

/*  Derived class that encapsulates the Transmit Request frame type.
*/
class TxRequest : public ApiFrame {
public:
    /* Constructors - allows for support of hardware and software serial ports */
    TxRequest(HardwareSerial * const serial) : ApiFrame(serial) {}
    TxRequest(SoftwareSerial * const serial) : ApiFrame(serial) {}
    
    /* Address of receiving module. defaults to controller. */
    uint64_t LongAddress = CONTROLLER_64BIT_ADDRESS;
    
    /* Network address of receiving module */
    uint16_t ShortAddress = DESTINATION_16BIT_NETWORK_ADDRESS_UNKNOWN;
    
    /* Optional parameters */
    uint8_t RadiusOffset;
    uint8_t Options;
    
    /*  Assembles TXREQ frame and sends out over the serial line. Does not support escaping.
    
        Note that the data payload (*buffer) is generally limited to 72 bytes when transmitting
        in the clear. Security reduces that to 54 bytes. APS (end-to-end security) reduces it
        futher to 45 bytes. Keep that in mind when sending data. End to end security is enabled
        when Options bit 0x20 is on. Individual packets can be secured on a case by case basis
        by using the overloaded method below.
        
        Btw, these byte limits aren't absolute. These are what I was able to derive from source
        data, so don't take them as gospel.
        
        Frame id is only required when sending secure. Otherwise, defaults to 0 unless specified.
    */
    void Write(uint8_t *buffer, uint8_t length, uint8_t frameId = 0){ Write(buffer, length, false, frameId); }
    void Write(uint8_t *buffer, uint8_t length, bool useEndToEndSecuirty, uint8_t frameId);

protected:
    uint8_t FrameType = 0x10;
    bool _useEndToEndSecurity;
};

/*  Derived class that encapsulates the Receive Packet frame type.
*/
class RxPacket : public ApiFrame {
public:
    /* Constructors - allows for support of hardware and software serial ports */
    RxPacket(HardwareSerial * const serial) : ApiFrame(serial) {}
    RxPacket(SoftwareSerial * const serial) : ApiFrame(serial) {}
    
    /* Address of transmitting module. defaults to controller. */
    uint64_t LongAddress = CONTROLLER_64BIT_ADDRESS;
    
    /* Network address of transmitting module */
    uint16_t ShortAddress = DESTINATION_16BIT_NETWORK_ADDRESS_UNKNOWN;
    
    /* Optional parameter */
    uint8_t Options = 0;
    
    /* Array containing bytes received from sending device. the amount of data
       received from the source varies. 72 is the nominal maximum size when receiving
       data in the clear. security reduces that amount to as low as 45 bytes.
   */
    uint8_t Payload[72];
    uint8_t PayloadLength;
    
    uint8_t Read();
    
protected:
    uint8_t FrameType = 0x90;
};

#endif
