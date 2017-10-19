#include "BNO055.h"

uint8_t BNO055::begin(void){
    return begin(IMU_OPERATION_MODE_NDOF);
}

uint8_t BNO055::begin(uint8_t operatingMode){
    uint8_t b;
    
    //initialize i2c bus
    Wire.begin();
    
    //wait for unit to boot
    delay(1000); // hold on for boot
    
    //set the power mode to normal
    b = setOperatingMode(IMU_OPERATION_MODE_CONFIG);
    if(b != IMU_ERROR_NONE){ return b; }
    delay(100);
    
    //turn the device on
    if(writeInt(BNO055_PWR_MODE_ADDR, BNO055_POWER_MODE_NORMAL) == false){
        return IMU_ERROR_RESET_PWR_MODE_WRITE;
    }
    delay(100);
    
    //range check the operating mode then set it
    //for now - i'm only supporting NDOF. this is looking forward in case i decide to
    //support other operations. we'll see.
    if(operatingMode != IMU_OPERATION_MODE_NDOF){ operatingMode = IMU_OPERATION_MODE_NDOF; }
    b = setOperatingMode(operatingMode);
    if(b != IMU_ERROR_NONE){ return b; }
    delay(100);
    
    _lastReadTicks = millis();
    
    return IMU_ERROR_NONE;
}

uint8_t BNO055::read(){
    //wait at least 25ms after last read.
    if((millis() - _lastReadTicks) < 25){
        return IMU_STATUS_READING;
    }
    
    //retrieve heading, roll and pitch values in a single 6 byte array
    if(readBytes(BNO055_EULER_VALUES_ADDR, _data, 6) == false){
        errorCode = IMU_ERROR_READ;
        return IMU_STATUS_ERROR;
    }
    
    //track the last successful read ticks
    _lastReadTicks = millis();
    
    //lsb preceeds msb for each parameter
    int16_t h = ((int16_t)_data[0]) | (((int16_t)_data[1]) << 8);
    int16_t r = ((int16_t)_data[2]) | (((int16_t)_data[3]) << 8);
    int16_t p = ((int16_t)_data[4]) | (((int16_t)_data[5]) << 8);
    
    //final calcs
    heading = ((float)h) / 16.0;
    roll = ((float)r) / 16.0;
    pitch = ((float)p) / 16.0;
    
    return IMU_STATUS_SUCCESS;
}

uint8_t BNO055::setOperatingMode(uint8_t mode){
    _mode = mode;
    if(writeInt(BNO055_OPR_MODE_ADDR, _mode)){
        delay(30);
        return IMU_ERROR_NONE;
    }
    errorCode = IMU_ERROR_SET_OP_MODE;
    return IMU_STATUS_ERROR;
}

