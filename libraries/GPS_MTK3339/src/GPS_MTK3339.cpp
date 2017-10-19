#include "GPS_MTK3339.h"

//#define GPS_DEBUG_READ_VERBOSE
//#define GPS_DEBUG_READ_PRINT_BUFFER
//#define GPS_DEBUG_READ
#ifdef GPS_DEBUG_READ
    #define GPS_DEBUG_READ_PRINT(v) Serial.print(v)
    #define GPS_DEBUG_READ_PRINTF(v,f) Serial.print(v,f)
    #define GPS_DEBUG_READ_PRINTLN(v) Serial.println(v)
    #define GPS_DEBUG_READ_PRINTFLN(v,f) Serial.println(v,f)
    #define GPS_DEBUG_READ_PRINTBYTE(v) if(v<0x10){Serial.print("0");}Serial.print(b,HEX);Serial.print(" ");
#else
    #define GPS_DEBUG_READ_PRINT(v)
    #define GPS_DEBUG_READ_PRINTF(v,f)
    #define GPS_DEBUG_READ_PRINTLN(v)
    #define GPS_DEBUG_READ_PRINTFLN(v,f)
    #define GPS_DEBUG_READ_PRINTBYTE(v)
#endif

GPS_MTK3339::GPS_MTK3339(HardwareSerial* s) : _hserial(s) { _useSserial = false; }
GPS_MTK3339::GPS_MTK3339(SoftwareSerial* s) : _sserial(s) { _useSserial = true; }

void GPS_MTK3339::Send(const char* str){
    if(_useSserial){ _sserial->println(str); }
    else{ _hserial->println(str); }
}

uint8_t GPS_MTK3339::Read(){
    #ifdef GPS_DEBUG_READ_VERBOSE
        GPS_DEBUG_READ_PRINTLN("READ GPS");
    #endif
    
    switch(_machineState){
        case GPS_MS_INIT:
        case GPS_MS_ERROR:
        case GPS_MS_READY:
            return startRead();
    }
    return continueRead();
}

uint8_t GPS_MTK3339::startRead(){
    #ifdef GPS_DEBUG_READ_VERBOSE
        if(serial_available() > 0){
            GPS_DEBUG_READ_PRINTLN("GPS DATA IN BUFFER");
        }
        GPS_DEBUG_READ_PRINTLN("READ GPS");
    #endif
    while(serial_available() > 0){
        uint8_t b = serial_read();
        if(b == GPS_START_DELIM){
            memset(Buffer, 0x00, sizeof(Buffer));
            Buffer[0] = b;
            _bufferOffset = 1;
            _machineState = GPS_MS_READING;
            return continueRead();
        }
    }
    return GPS_STATUS_NODATA;
}

uint8_t GPS_MTK3339::continueRead(){
    #ifdef GPS_DEBUG_READ_VERBOSE
        GPS_DEBUG_READ_PRINTLN("READ GPS CONTINUE");
    #endif
    while(serial_available() > 0){
        char b = (char)serial_read();
        if(b == GPS_START_DELIM){
            GPS_DEBUG_READ_PRINTLN("unexpected start delimiter found");
            _machineState = GPS_MS_ERROR;
            return GPS_ERROR_PARSE_ERR;
        }
        if(b == GPS_CHKSUM_DELIM){
            writeBuffer(b);
            uint32_t ticks = millis();
            while(serial_available() < 2){
                if(millis() - ticks > 250){
                    GPS_DEBUG_READ_PRINTLN("too long to read checksum bytes");
                    _machineState = GPS_MS_ERROR;
                    return GPS_ERROR_TIMEOUT;
                }
            }
            b = serial_read();
            writeBuffer(b);
            
            b = serial_read();
            writeBuffer(b);
            
            writeBuffer(0x00);
            
            return parseSentence();
        }
        writeBuffer(b);
    }
    return GPS_STATUS_READING;
}

void GPS_MTK3339::writeBuffer(uint8_t b){
    Buffer[_bufferOffset] = b;
    _bufferOffset++;
}

uint8_t GPS_MTK3339::parseSentence(){
    GPS_DEBUG_READ_PRINTLN("PARSING");
    
    _machineState = GPS_MS_READY;
    
    #ifdef GPS_DEBUG_READ_PRINT_BUFFER
        GPS_DEBUG_READ_PRINTLN((char *)Buffer);
    #endif
    
    uint8_t sentenceName = getsentenceName();
    uint8_t startByte = 0;
    uint8_t stopByte = startByte;
    uint8_t element = 0;
    bool elementParseSuccess = false;
    
    for(uint8_t i = 0; i < sizeof(Buffer); i++){
        uint8_t b = Buffer[i];
        
        // ',' or '*'
        if(b == GPS_ELEMENT_DELIM || b == GPS_CHKSUM_DELIM){
            switch(sentenceName){
                case GPS_STATUS_SUCCESS_RMC:
                    elementParseSuccess = parseRmc(element, startByte, stopByte);
                    break;
                case GPS_STATUS_SUCCESS_GGA:
                    elementParseSuccess = parseGga(element, startByte, stopByte);
                    break;
                default:
                    elementParseSuccess = true;
                    break;
            }
            if(elementParseSuccess == false){
                GPS_DEBUG_READ_PRINTLN("element parse error");
                _machineState = GPS_MS_ERROR;
                return GPS_ERROR_PARSE_ERR;
            }
            if(b == GPS_CHKSUM_DELIM){
                if(verifyChecksum(i)){ 
                    loadValues();
                    return sentenceName; 
                }
                
                GPS_DEBUG_READ_PRINTLN("invalid checksum");
                _machineState = GPS_MS_ERROR;
                return GPS_ERROR_CHECKSUM;
            }
            startByte = i + 1;
            stopByte = startByte;
            element++;
        }
        else{
            stopByte++;
        }
    }
    
    GPS_DEBUG_READ_PRINTLN("unexpected end of parse");
    _machineState = GPS_MS_ERROR;
    return GPS_ERROR_PARSE_ERR;
}

uint8_t GPS_MTK3339::getsentenceName(){
    uint8_t sentenceName = GPS_STATUS_SUCCESS_OTH;
    uint8_t cmp = memcmp(Buffer, "$GPRMC", 6);
    if(cmp == 0){
        GPS_DEBUG_READ_PRINTLN("parseRmc");
        sentenceName = GPS_STATUS_SUCCESS_RMC;
    }
    else{
        cmp = memcmp(Buffer, "$GPGGA", 6);
        if(cmp == 0){
            GPS_DEBUG_READ_PRINTLN("parseGga");
            sentenceName = GPS_STATUS_SUCCESS_GGA;
        }
    }
    return sentenceName;
}

bool GPS_MTK3339::verifyChecksum(uint8_t start){
    return true;
}

void GPS_MTK3339::loadValues(){
    FixTime = _tempValues.fixTime;
    FixQuality = _tempValues.fixQuality;
    Precision = _tempValues.precision;
    Status = _tempValues.status;
    StatusChar = _tempValues.statusChar;
    Mode = _tempValues.mode;
    Longitude = normalizeDegrees(_tempValues.longitude);
    Latitude = normalizeDegrees(_tempValues.latitude);
    Altitude = _tempValues.altitude;
    Geoid = _tempValues.geoid;
    GroundSpeed = _tempValues.groundSpeed;
    GroundTrack = _tempValues.groundTrack;
    MagneticVariation = _tempValues.magneticVariation;
}

//-82.36,-8221.8518   27.71,2742.4665
float GPS_MTK3339::normalizeDegrees(float value){
    value /= 100.0F;
    float degrees = trunc(value);
    float minutes = (value - degrees) * 100;
    minutes /= 60.0F;
    value = degrees + minutes;
    return value;
}

bool GPS_MTK3339::parseRmc(uint8_t element, uint8_t startByte, uint8_t stopByte){
    bool validParse = true;
    char* start = (char*)Buffer + startByte;
    
    switch(element){
        //to floats:
        case 1:
            _tempValues.fixTime = (float)atof(start);
            if(_tempValues.fixTime == 0.0F) {
                GPS_DEBUG_READ_PRINT("invalid parse - ");
                validParse = false; 
            }
            GPS_DEBUG_READ_PRINT("\trmc: fix time - ");
            GPS_DEBUG_READ_PRINTLN(_tempValues.fixTime);
            break;
            
        case 7:
            _tempValues.groundSpeed = (float)atof(start);
            GPS_DEBUG_READ_PRINT("\trmc: gnd speed - ");
            GPS_DEBUG_READ_PRINTLN(_tempValues.groundSpeed);
            break;
            
        case 8:
            _tempValues.groundTrack = (float)atof(start);
            GPS_DEBUG_READ_PRINT("\trmc: gnd track - ");
            GPS_DEBUG_READ_PRINTLN(_tempValues.groundTrack);
            return true;
            
        case 10:
            _tempValues.magneticVariation = (float)atof(start);
            GPS_DEBUG_READ_PRINT("\trmc: mag var - ");
            GPS_DEBUG_READ_PRINTLN(_tempValues.magneticVariation);
            break;
            
            
        case 2:     //status: (A)ctive, (V)oid
            switch((char)Buffer[startByte]){
                case 'A': _tempValues.status = GPS_STATUS_ACTIVE; _tempValues.statusChar = 'A'; break;
                case 'V': _tempValues.status = GPS_STATUS_VOID; _tempValues.statusChar = 'V'; break;
                default: _tempValues.status = GPS_STATUS_UNKNOWN; _tempValues.statusChar = 'U'; break;
            }
            GPS_DEBUG_READ_PRINT("\trmc: status - ");
            GPS_DEBUG_READ_PRINTLN(_tempValues.status);
            break;
            
        case 11:    //E/W
            switch(Buffer[startByte]){
                case 'E': _tempValues.magneticVariation *= -1; break;
            }
            GPS_DEBUG_READ_PRINT("rmc: mag var E/W - ");
            GPS_DEBUG_READ_PRINTLN(_tempValues.magneticVariation);
            break;
            
        case 12:    //mode: (A)utonomous, (D)ifferential, (E)stimated, (N)otValid, (S)imulator
            switch((char)Buffer[startByte]){
                case 'A': _tempValues.mode = GPS_MODE_AUTONOMOUS; break;
                case 'D': _tempValues.mode = GPS_MODE_DIFFERENTIAL; break;
                case 'E': _tempValues.mode = GPS_MODE_ESTIMATED; break;
                case 'N': _tempValues.mode = GPS_MODE_NOT_VALID; break;
                case 'S': _tempValues.mode = GPS_MODE_SIMULATOR; break;
                default: _tempValues.mode = GPS_MODE_UNKNOWN; break;
            }
            GPS_DEBUG_READ_PRINT("rmc: mode - ");
            GPS_DEBUG_READ_PRINTLN(_tempValues.mode);
            break;
        default:
            //GPS_DEBUG_READ_PRINTLN("*");
            break;
    }

    return validParse;
}

bool GPS_MTK3339::parseGga(uint8_t element, uint8_t startByte, uint8_t stopByte){
    bool validParse = true;
    char* start = (char*)Buffer + startByte;
    
    switch(element){
        case 6:
            _tempValues.fixQuality = (uint8_t)atoi(start);;
            GPS_DEBUG_READ_PRINT("\tgga: fix quality - ");
            GPS_DEBUG_READ_PRINTLN(_tempValues.fixQuality);
            break;
            
        case 2:
            _tempValues.latitude = (float)atof(start);
            GPS_DEBUG_READ_PRINT("\tgga: latitude raw - ");
            GPS_DEBUG_READ_PRINTLN(_tempValues.latitude);
            break;
            
        case 4:
            _tempValues.longitude = (float)atof(start);
            GPS_DEBUG_READ_PRINT("\tgga: longitude raw - ");
            GPS_DEBUG_READ_PRINTLN(_tempValues.longitude);
            break;
            
        case 8:
            _tempValues.precision = (float)atof(start);
            GPS_DEBUG_READ_PRINT("\tgga: precision - ");
            GPS_DEBUG_READ_PRINTLN(_tempValues.precision);
            break;
            
        case 9:
            _tempValues.altitude = (float)atof(start);
            GPS_DEBUG_READ_PRINT("\tgga: altitude - ");
            GPS_DEBUG_READ_PRINTLN(_tempValues.altitude);
            break;
            
        case 11:
            _tempValues.geoid = (float)atof(start);
            GPS_DEBUG_READ_PRINT("\tgga: geoid - ");
            GPS_DEBUG_READ_PRINTFLN(_tempValues.geoid, 2);
            break;
            
        case 3:     //N/S
            switch((char)Buffer[startByte]){
                case 'S': _tempValues.latitude *= -1; break;
            }
            GPS_DEBUG_READ_PRINT("\tgga: latitude normalized - ");
            GPS_DEBUG_READ_PRINT(" ");
            GPS_DEBUG_READ_PRINTF(normalizeDegrees(_tempValues.latitude), 4);
            GPS_DEBUG_READ_PRINTLN(_tempValues.latitude < 0.0 ? 'S' : 'N');
            break;
            
        case 5:    //E/W
            switch((char)Buffer[startByte]){
                case 'W': _tempValues.longitude *= -1; break;
            }
            GPS_DEBUG_READ_PRINT("\tgga: longitude normalized - ");
            GPS_DEBUG_READ_PRINT(" ");
            GPS_DEBUG_READ_PRINTF(normalizeDegrees(_tempValues.longitude), 4);
            GPS_DEBUG_READ_PRINTLN(_tempValues.longitude < 0.0 ? 'W' : 'E');
            break;
    }
 
    return validParse;
    
    /*
    GGA - essential fix data which provide 3D location and accuracy data. 
    $GPGGA,     0
    123519,     1
    4807.038,   2   Latitude
    N,          3   N/S
    01131.000,  4   Longitude
    E,          5   E/W
    1,          6   Fix Qual
    08,         7
    0.9,        8   Precision
    545.4,      9   Alitude
    M,          10  M/F
    46.9,       11  geoid
    M,          12  M/F
    ,           13  DGPS time
    *47         14  DGPS id
    
    Where:
         GGA          Global Positioning System Fix Data
         123519       Fix taken at 12:35:19 UTC
         4807.038,N   Latitude 48 deg 07.038' N
         01131.000,E  Longitude 11 deg 31.000' E
         1            Fix quality: 0 = invalid
                                   1 = GPS fix (SPS)
                                   2 = DGPS fix
                                   3 = PPS fix
                                   4 = Real Time Kinematic
                                   5 = Float RTK
                                   6 = estimated (dead reckoning) (2.3 feature)
                                   7 = Manual input mode
                                   8 = Simulation mode
         08           Number of satellites being tracked
         0.9          Horizontal dilution of position
         545.4,M      Altitude, Meters, above mean sea level
         46.9,M       Height of geoid (mean sea level) above WGS84 ellipsoid
         (empty field) time in seconds since last DGPS update
         (empty field) DGPS station ID number
         *47          the checksum data, always begins with *


    If the height of geoid is missing then the altitude should be suspect. 
    Some non-standard implementations report altitude with respect to the 
    ellipsoid rather than geoid altitude. Some units do not report negative 
    altitudes at all. This is the only sentence that reports altitude. 
    */
    return true;
}


