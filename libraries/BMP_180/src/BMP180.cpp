#include "BMP180.h"

bool BMP180::begin() {
    return begin(BMP180_ULTRA_LOW_POWER);
}

bool BMP180::begin(uint8_t resolution) {
    float c3,c4,b1;
    
    I2CLib::begin();
    
    //these are 32 bit values, but sensor returns as 16 bits
    int16_t ac1_16, ac2_16, ac3_16, vb1_16, vb2_16, mb_16, mc_16, md_16;
    uint16_t ac4_16, ac5_16, ac6_16;
    
    if(!readInt(0xAA,  ac1_16) ||
       !readInt(0xAC,  ac2_16) ||
       !readInt(0xAE,  ac3_16) ||
       !readInt(0xB0, ac4_16) ||
       !readInt(0xB2, ac5_16) ||
       !readInt(0xB4, ac6_16) ||
       !readInt(0xB6,  vb1_16) ||
       !readInt(0xB8,  vb2_16) ||
       !readInt(0xBA,  mb_16) ||
       !readInt(0xBC,  mc_16) ||
       !readInt(0xBE,  md_16)
    )
    {
        return false;
    }
    
    AC1 = (int32_t)ac1_16;
    AC2 = (int32_t)ac2_16;
    AC3 = (int32_t)ac3_16;
    AC4 = (uint32_t)ac4_16;
    AC5 = (uint32_t)ac5_16;
    AC6 = (uint32_t)ac6_16;
    VB1 = (int32_t)vb1_16;
    VB2 = (int32_t)vb2_16;
    MB = (int32_t)mb_16;
    MC = (uint32_t)mc_16;
    MD = (uint32_t)md_16;
    
    setOversample(resolution);
    
    c3 = 160.0 * pow(2,-15) * AC3;
    c4 = pow(10,-3) * pow(2,-15) * AC4;
    b1 = pow(160,2) * pow(2,-30) * VB1;
    c5 = (pow(2,-15) / 160) * AC5;
    c6 = AC6;
    mc = (pow(2,11) / pow(160,2)) * MC;
    md = MD / 160.0;
    x0 = AC1;
    x1 = 160.0 * pow(2,-13) * AC2;
    x2 = pow(160,2) * pow(2,-25) * VB2;
    y0 = c4 * pow(2,15);
    y1 = c4 * c3;
    y2 = c4 * b1;
    p0 = (3791.0 - 8.0) / 1600.0;
    p1 = 1.0 - 7357.0 * pow(2,-20);
    p2 = 3038.0 * 100.0 * pow(2,-36);
    
    return true;
}

uint8_t BMP180::read(){
    switch(currentStep){
        case BMP_STEP_START_TEMP:
            return startTemperature();
        case BMP_STEP_WAIT_TEMP:
            return waitTemperature();
        case BMP_STEP_START_PRESS:
            return startPressure();
        case BMP_STEP_WAIT_PRESS:
            return waitPressure();
        case BMP_STEP_READ_VALUES:
            return readCompensatedValues();
    }
    currentStep = BMP_STEP_START_TEMP;
    return BMP_STATUS_ERROR;
}

uint8_t BMP180::startTemperature(){
    delayTicks = writeInt(BMP180_REG_CONTROL, BMP180_CMD_TEMPERATURE) ? 5 : 0;
    
    currentTicks = millis();

    if(delayTicks == 0){
        return BMP_STATUS_ERROR;
    }
    
    currentStep = BMP_STEP_WAIT_TEMP;
    return BMP_STATUS_READING;
}

uint8_t BMP180::waitTemperature(){
    if((millis() - currentTicks) >= delayTicks){
        #ifdef BMP180_USE_DEFAULTS
            uncompTemp = 27898;
        #else
            int16_t value;
            if(readInt(BMP180_REG_RESULT, value)){
                uncompTemp = (float)value;
            }
            else{
                currentStep = BMP_STEP_START_TEMP;
                return BMP_STATUS_ERROR;
            }
        #endif
        currentStep = BMP_STEP_START_PRESS;
    }

    return BMP_STATUS_READING;
}

uint8_t BMP180::startPressure() {
    uint8_t waitTicks;
    
    uint8_t mode;
    switch (oversampling)
    {
        case 1:
            mode = BMP180_COMMAND_STD_MODE;
            waitTicks = 8;
            break;
        case 2:
            mode = BMP180_COMMAND_HI_RES_MODE;
            waitTicks = 14;
            break;
        case 3:
            mode = BMP180_COMMAND_ULT_HI_RES_MODE;
            waitTicks = 26;
            break;
        default:
            mode = BMP180_COMMAND_LOW_POWER_MODE;
            waitTicks = 5;
            break;
    }
    
    delayTicks = writeInt(BMP180_REG_CONTROL, mode) ? waitTicks : 0;
    currentTicks = millis();
    if(delayTicks == 0){
        currentStep = BMP_STEP_START_TEMP;
        return BMP_STATUS_ERROR;
    }
    
    currentStep = BMP_STEP_WAIT_PRESS;
    return BMP_STATUS_READING;
}

uint8_t BMP180::waitPressure(){
    if((millis() - currentTicks) >= delayTicks){
        #ifdef BMP180_USE_DEFAULTS
            uncompPress = 23843;
        #else
            uint8_t data[3];
            if(readBytes(BMP180_REG_RESULT, data, 3)){
                uncompPress = (data[0] * 256.0) + data[1] + (data[2]/256.0);
            }
            else{
                currentStep = BMP_STEP_START_TEMP;
                return BMP_STATUS_ERROR;
            }
        #endif
        currentStep = BMP_STEP_READ_VALUES;
    }
    return BMP_STATUS_READING;
}

uint8_t BMP180::readCompensatedValues(){
    float a,s,x,y,z;

    a = c5 * (uncompTemp - c6);
    tempC = a + (mc / (a + md));
    tempF = (tempC * 1.8) + 32.0;

    s = tempC - 25.0;
    x = (x2 * pow(s,2)) + (x1 * s) + x0;
    y = (y2 * pow(s,2)) + (y1 * s) + y0;
    z = (uncompPress - x) / y;
    pressMb = (p2 * pow(z,2)) + (p1 * z) + p0;
    pressPa = pressMb * 100.0;
    pressInHg = pressMb * 0.02953;
    
    currentStep = BMP_STEP_START_TEMP;
    return BMP_STATUS_SUCCESS;
}

void BMP180::setOversample(uint8_t value){
    if(value <= BMP180_ULTRA_HIGH_RES){ oversampling = value; }
    else { oversampling = BMP180_ULTRA_LOW_POWER; }
}


