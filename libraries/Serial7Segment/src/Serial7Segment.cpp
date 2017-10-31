#include "Serial7Segment.h"

void Serial7Segment::begin() {
    I2CLib::begin();
}

void Serial7Segment::clear(){
    writeInt(deviceAddress, SERIAL_7_CLEAR_COMMAND);
}

void Serial7Segment::decimalControl(uint8_t bitmask){
    _buffer[0] = SERIAL_7_DECIMAL_CONTROL_COMMAND;
    _buffer[1] = bitmask;
    writeBytes(deviceAddress, _buffer, 2);
}

void Serial7Segment::setCursor(uint8_t cursorPostion){
    _buffer[0] = SERIAL_7_CURSOR_COMMAND;
    _buffer[1] = cursorPostion;
    writeBytes(deviceAddress, _buffer, 2);
}

void Serial7Segment::setBrightness(uint8_t brightness){
    _buffer[0] = SERIAL_7_BRIGHTNESS_COMMAND;
    _buffer[1] = brightness;
    writeBytes(deviceAddress, _buffer, 2);
}

void Serial7Segment::setDigitSegments(uint8_t digit, uint8_t segments){
    if(digit > 3){ return; }
    switch(digit){
        case 0: _buffer[0] = SERIAL_7_DIGIT_4_COMMAND; break;
        case 1: _buffer[0] = SERIAL_7_DIGIT_3_COMMAND; break;
        case 2: _buffer[0] = SERIAL_7_DIGIT_2_COMMAND; break;
        case 3: _buffer[0] = SERIAL_7_DIGIT_1_COMMAND; break;
        default: return;
    }
    _buffer[0] = SERIAL_7_BRIGHTNESS_COMMAND;
    _buffer[1] = segments;
    writeBytes(deviceAddress, _buffer, 2);
}

void Serial7Segment::factoryReset(void){
    writeInt(deviceAddress, SERIAL_7_FACTORY_RESET);
}

void Serial7Segment::printString(String value){
    uint8_t buffer[6];
    buffer[0] = SERIAL_7_CURSOR_COMMAND;
    buffer[1] = SERIAL_7_CURSOR_4;
    for (uint8_t i = 0; i < 4; i++)
    {
        buffer[i + 2] = (uint8_t)value[i];
    }
    writeBytes(deviceAddress, buffer, sizeof(buffer));
}

void Serial7Segment::writeTime(uint8_t t1, uint8_t t2, bool colonOn, bool leadingZerosT1){
    char tempString[6];
    if(leadingZerosT1){
        sprintf(tempString, "%02d%02d", t1, t2);
    }
    else{
        sprintf(tempString, "%2d%02d", t1, t2);
    }
    
    uint8_t buffer[8];
    buffer[0] = SERIAL_7_CURSOR_COMMAND;
    buffer[1] = SERIAL_7_CURSOR_4;
    for(uint8_t i = 0; i < 4; i++){
        buffer[i + 2] = tempString[i];
    }
    buffer[6] = SERIAL_7_DECIMAL_CONTROL_COMMAND;
    buffer[7] = colonOn ? SERIAL_7_DECIMAL_CONTROL_COLON : 0x00;
    
    writeBytes(deviceAddress, buffer, sizeof(buffer));
}

void Serial7Segment::writeHex(uint8_t value){
    writeHex((uint16_t)value);
}

void Serial7Segment::writeHex(uint16_t value){
    uint8_t buffer[6];
    
    buffer[0] = SERIAL_7_CURSOR_COMMAND;
    buffer[1] = SERIAL_7_CURSOR_4;
    buffer[2] = ((uint8_t)(value >> 12)) & 0x0F;
    buffer[3] = ((uint8_t)(value >> 8)) & 0x0F;
    buffer[4] = ((uint8_t)(value >> 4)) & 0x0F;
    buffer[5] = ((uint8_t)value) & 0x0F;

    writeBytes(deviceAddress, buffer, sizeof(buffer));
}

void Serial7Segment::writeFloat(float value, uint8_t precision, char buffer[]){
    int16_t intPart;
    uint16_t fracPart;
    uint8_t outBuffer[8];
    uint8_t offset;
    
    parseFloat(value, precision, intPart, fracPart);
    bool isNeg = value < 0;
    intPart = abs(intPart);
    
    if(intPart < 10){ offset = 3; }
    else if(intPart < 100) { offset = 2; }
    else {offset = 1; }
    offset -= precision;
    
    sprintf(buffer, "    ");
    sprintf(buffer + offset, "%d%d", intPart, fracPart);
    
    outBuffer[0] = SERIAL_7_CURSOR_COMMAND;
    outBuffer[1] = SERIAL_7_CURSOR_4;
    for (uint8_t i = 0; i < 4; i++)
    {
        outBuffer[i + 2] = (uint8_t)buffer[i];
    }
    outBuffer[6] = SERIAL_7_DECIMAL_CONTROL_COMMAND;
    switch(precision){
        case 0: outBuffer[7] = 0; break;
        case 1: outBuffer[7] = SERIAL_7_DECIMAL_CONTROL_DIGIT_3; break;
        case 2: outBuffer[7] = SERIAL_7_DECIMAL_CONTROL_DIGIT_2; break;
        case 3: outBuffer[7] = SERIAL_7_DECIMAL_CONTROL_DIGIT_1; break;
    }
    
    if(isNeg){ outBuffer[2] = '-'; }
    
    writeBytes(deviceAddress, outBuffer, sizeof(outBuffer));
}

//break a float value into its integer and fractional parts
void Serial7Segment::parseFloat(float value, uint8_t precision, int16_t &intPart, uint16_t &fracPart){
    if(precision > 5){ precision = 5; }
    uint16_t a = pow(10, precision);
    
    intPart = (int16_t)(value);
    value -= intPart;
    
    fracPart = (uint16_t)abs((value * a));
}



