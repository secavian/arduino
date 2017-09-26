#include <I2CLib.h>

void I2CLib::begin(){ Wire.begin(); }

bool I2CLib::readInt(uint8_t address, int8_t &value) {
    uint8_t tmp;
    if (readInt(address, tmp)) {
        value = (int8_t)tmp;
        return true;
    }
    return false;
}

bool I2CLib::readInt(uint8_t address, uint8_t &value) {
    if (readBytes(address, _buffer, 1))
    {
        value = _buffer[0];
        return true;
    }
    return false;
}

bool I2CLib::readInt(uint8_t address, int16_t &value) {
    uint16_t tmp;
    if (readInt(address, tmp)) {
        value = (int16_t)tmp;
        return true;
    }
    return false;
}

bool I2CLib::readInt(uint8_t address, uint16_t &value) {
    if (readBytes(address, _buffer, 2))
    {
        value = (((uint16_t)_buffer[0] << 8) | (uint16_t)_buffer[1]);
        return true;
    }
    return false;
}

bool I2CLib::readInt(uint8_t address, int32_t &value) {
    uint32_t tmp;
    if (readInt(address, tmp)) {
        value = (int32_t)tmp;
        return true;
    }
    return false;
}

bool I2CLib::readInt(uint8_t address, uint32_t &value) {
    if (readBytes(address, _buffer, 2))
    {
        value = (((uint32_t)_buffer[0] << 24) | ((uint32_t)_buffer[1] << 16) | ((uint32_t)_buffer[2] << 8) | (uint32_t)_buffer[3]);
        return true;
    }
    return false;
}

bool I2CLib::readBytes(uint8_t address, uint8_t* values, uint8_t length) {
    Wire.beginTransmission(deviceAddress);
    Wire.write((uint8_t)address);
    if(Wire.endTransmission() == 0) {
        Wire.requestFrom((uint8_t)deviceAddress, length);
        while(Wire.available() != length) ; // wait until bytes are ready
        for(uint8_t x = 0; x < length; x++) {
            values[x] = Wire.read();
        }
        return true;
    }
    return false;
}

bool I2CLib::writeInt(uint8_t address, int8_t value) {
    return writeInt(address, (uint8_t)value);
}

bool I2CLib::writeInt(uint8_t address, uint8_t value) {
    _buffer[0] = (uint8_t)value;
    return writeBytes(address, _buffer, 1);
}

bool I2CLib::writeInt(uint8_t address, int16_t value) {
    return writeInt(address, (uint16_t)value);
}

bool I2CLib::writeInt(uint8_t address, uint16_t value) {
    _buffer[0] = (uint8_t)(value >> 8);
    _buffer[1] = (uint8_t)value;
    return writeBytes(address, _buffer, 2);
}

bool I2CLib::writeInt(uint8_t address, int32_t value) {
    return writeInt(address, (uint32_t)value);
}

bool I2CLib::writeInt(uint8_t address, uint32_t value) {
    _buffer[0] = (uint8_t)(value >> 24);
    _buffer[1] = (uint8_t)(value >> 16);
    _buffer[2] = (uint8_t)(value >> 8);
    _buffer[3] = (uint8_t)value;
    return writeBytes(address, _buffer, 4);
}

bool I2CLib::writeBytes(uint8_t address, uint8_t* values, uint8_t length) {
    Wire.beginTransmission(deviceAddress);
    Wire.write(&address, 1);
    Wire.write(values, length);
    return Wire.endTransmission() == 0;
}
