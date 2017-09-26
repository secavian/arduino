#ifndef _BYTE_CONVERTER_LIB_H_
#define _BYTE_CONVERTER_LIB_H_

/* UNTESTED - TEST BEFORE ENABLING THIS MACRO*/
//#define SUPPORT_DOUBLE

//converter class for moving data back and forth between arrays.
class ByteConverter{
public:
    /*  pass in an array of unsigned bytes and extract the float value encoded starting
        at the specified offset. byte order can be msb first (default) or lsb first.
    
        an overflow can occur if offset is not valid and/or if the buffer is undersized.
        this will likely not harm anything since the write action is to an array this class
        manages however calling processes should range check the offst against the buffer size
        if there is any concern. results will be invalid in those cases. floats use 4 bytes
        and offset + 3 should not exceed the last element of the array.
    */
    float getFloat(uint8_t * buffer, uint8_t offset, bool msbFirst = true){
        converter_t  floatToByte;
        
        for(uint8_t i = 0; i < 4; i++){
            if(msbFirst){
                floatToByte.bytes[i] = buffer[offset + i];
            }
            else{
                floatToByte.bytes[3 - i] = buffer[offset + i];
            }
        }
        return floatToByte.floatValue;
    }
    
    /*  pass in an array of unsigned bytes and extract the integer type value encoded starting
        at the specified offset. byte order can be msb first (default) or lsb first.
    
        an overflow can occur if offset is not valid and/or if the buffer is undersized.
        this will likely not harm anything since the write action is to an array this class
        manages however calling processes should range check the offst against the buffer size
        if there is any concern. results will be invalid in those cases. integer types use 2 to 8
        bytes and the offset + 1 (16 bit), offset + 3 (32 bit) or offset + 7 (64 bit) should not
        exceed the last element of the array.
    */
    int16_t getInt16(uint8_t *buffer, uint8_t offset, bool msbFirst = true){ return (int16_t)getUInt16(buffer, offset, msbFirst); }
    uint16_t getUInt16(uint8_t *buffer, uint8_t offset, bool msbFirst = true){
        uint16_t value;
        if(msbFirst){
            value = ((uint16_t)buffer[offset] << 8);
            value |= (uint16_t)buffer[offset + 1];
        }
        else{
            value = (uint16_t)buffer[offset];
            value |= ((uint16_t)buffer[offset + 1]  << 8);
        }
        return value;
    }
    
    int32_t getInt32(uint8_t *buffer, uint8_t offset, bool msbFirst = true){ return (int32_t)getUInt32(buffer, offset, msbFirst); }
    uint32_t getUInt32(uint8_t *buffer, uint8_t offset, bool msbFirst = true){
        uint32_t value;
        if(msbFirst){
            value = ((uint32_t)buffer[offset] << 24);
            value |= ((uint32_t)buffer[offset + 1] << 16);
            value |= ((uint32_t)buffer[offset + 2] << 8);
            value |= (uint32_t)buffer[offset + 3];
        }
        else{
            value = (uint32_t)buffer[offset];
            value |= ((uint32_t)buffer[offset + 1] << 8);
            value |= ((uint32_t)buffer[offset + 2] << 16);
            value |= ((uint32_t)buffer[offset + 3] << 24);
        }
        return value;
    }
    
    int64_t getInt64(uint8_t *buffer, uint8_t offset, bool msbFirst = true){ return (int64_t)getUInt64(buffer, offset, msbFirst); }
    uint64_t getUInt64(uint8_t *buffer, uint8_t offset, bool msbFirst = true){
        uint64_t value;
        if(msbFirst){
            value = ((uint64_t)buffer[offset] << 56);
            value |= ((uint64_t)buffer[offset + 1] << 48);
            value |= ((uint64_t)buffer[offset + 2] << 40);
            value |= ((uint64_t)buffer[offset + 3] << 32);
            value |= ((uint64_t)buffer[offset + 4] << 24);
            value |= ((uint64_t)buffer[offset + 5] << 16);
            value |= ((uint64_t)buffer[offset + 6] << 8);
            value |= (uint64_t)buffer[offset + 7];
        }
        else{
            value = (uint64_t)buffer[offset];
            value |= ((uint64_t)buffer[offset + 1] << 8);
            value |= ((uint64_t)buffer[offset + 2] << 16);
            value |= ((uint64_t)buffer[offset + 3] << 24);
            value |= ((uint64_t)buffer[offset + 4] << 32);
            value |= ((uint64_t)buffer[offset + 5] << 40);
            value |= ((uint64_t)buffer[offset + 6] << 48);
            value |= ((uint64_t)buffer[offset + 7] << 56);
        }
        return value;
    }
    
    /*  pass in a float value and populate supplied array of unsigned bytes and starting at the specified
        offset. byte order can be msb first (default) or lsb first.
    
        an overflow can occur if offset is not valid and/or if the buffer is undersized. range check offset
        against the buffer size before calling into this method. this will write to 4 contiguous bytes.
    */
    void getBytes(float value, uint8_t * buffer, uint8_t offset, bool msbFirst = true){
        converter_t  floatToByte;
        
        floatToByte.floatValue = value;
        
        for(uint8_t i = 0; i < 4; i++){
            if(msbFirst){
                buffer[offset + i] = floatToByte.bytes[i];
            }
            else{
                buffer[offset + i] = floatToByte.bytes[3 - i];
            }
        }
    }
    
    /*  pass in a integer type value and populate supplied array of unsigned bytes and starting at the specified
        offset. byte order can be msb first (default) or lsb first.
    
        an overflow can occur if offset is not valid and/or if the buffer is undersized. range check offset
        against the buffer size before calling into this method. this will write to 2 contiguous bytes for
        16 bit values, 4 contiguous bytes for 32 bit values and 8 contiguous bytes for 64 bit values.
    */
    void getBytes(int16_t value, uint8_t * buffer, uint8_t offset, bool msbFirst = true){ getBytes((uint16_t)value, buffer, offset, msbFirst); }
    void getBytes(uint16_t value, uint8_t * buffer, uint8_t offset, bool msbFirst = true){
        if(msbFirst){
            buffer[offset] = (uint8_t)(value >> 8);
            buffer[offset + 1] = (uint8_t)value;
        }
        else{
            buffer[offset] = (uint8_t)value;
            buffer[offset + 1] = (uint8_t)(value >> 8);
        }
    }
    
    void getBytes(int32_t value, uint8_t * buffer, uint8_t offset, bool msbFirst = true){ getBytes((uint32_t)value, buffer, offset, msbFirst); }
    void getBytes(uint32_t value, uint8_t * buffer, uint8_t offset, bool msbFirst = true){
        if(msbFirst){
            buffer[offset] = (uint8_t)(value >> 24);
            buffer[offset + 1] = (uint8_t)(value >> 16);
            buffer[offset + 2] = (uint8_t)(value >> 8);
            buffer[offset + 3] = (uint8_t)value;
        }
        else{
            buffer[offset] = (uint8_t)value;
            buffer[offset + 1] = (uint8_t)(value >> 8);
            buffer[offset + 2] = (uint8_t)(value >> 16);
            buffer[offset + 3] = (uint8_t)(value >> 24);
        }
    }
    
    void getBytes(int64_t value, uint8_t * buffer, uint8_t offset, bool msbFirst = true){ getBytes((uint64_t)value, buffer, offset, msbFirst); }
    void getBytes(uint64_t value, uint8_t * buffer, uint8_t offset, bool msbFirst = true){
        if(msbFirst){
            buffer[offset] = (uint8_t)(value >> 56);
            buffer[offset + 1] = (uint8_t)(value >> 48);
            buffer[offset + 2] = (uint8_t)(value >> 40);
            buffer[offset + 3] = (uint8_t)(value >> 32);
            buffer[offset + 4] = (uint8_t)(value >> 24);
            buffer[offset + 5] = (uint8_t)(value >> 16);
            buffer[offset + 6] = (uint8_t)(value >> 8);
            buffer[offset + 7] = (uint8_t)value;
        }
        else{
            buffer[offset] = (uint8_t)value;
            buffer[offset + 1] = (uint8_t)(value >> 8);
            buffer[offset + 2] = (uint8_t)(value >> 16);
            buffer[offset + 3] = (uint8_t)(value >> 24);
            buffer[offset + 4] = (uint8_t)(value >> 32);
            buffer[offset + 5] = (uint8_t)(value >> 40);
            buffer[offset + 6] = (uint8_t)(value >> 48);
            buffer[offset + 7] = (uint8_t)(value >> 56);
        }
    }
    
    #ifdef SUPPORT_DOUBLE
    //UNTESTED CODE - BASED ON FLOAT METHODS ABOVE. ONLY ENABLE IF PLATFORM SUPPORTS 8 BYTE DOUBLE TYPES
    double getDouble(uint8_t * buffer, uint8_t offset, bool msbFirst = true){
        converter_d_t doubleToByte;
        
        for(uint8_t i = 0; i < 7; i++){
            if(msbFirst){
                doubleToByte.bytes[i] = buffer[offset + i];
            }
            else{
                doubleToByte.bytes[7 - i] = buffer[offset + i];
            }
        }
        return doubleToByte.doubleValue;
    }
    void getBytes(double value, uint8_t * buffer, uint8_t offset, bool msbFirst = true){
        converter_t  floatToByte;
        
        floatToByte.floatValue = value;
        
        for(uint8_t i = 0; i < 8; i++){
            if(msbFirst){
                buffer[offset + i] = floatToByte.bytes[i];
            }
            else{
                buffer[offset + i] = floatToByte.bytes[7 - i];
            }
        }
    }
    #endif
    
protected:
    union converter_t {
        uint8_t bytes[4];
        float floatValue;
    };
    
    #ifdef SUPPORT_DOUBLE
    union converter_d_t {
        uint8_t bytes[8];
        double doubleValue;
    };
    #endif
};

extern ByteConverter Convert;

#endif
