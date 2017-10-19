#ifndef _GPS_MTK3339_H
#define _GPS_MTK3339_H

#include <Arduino.h>
#include <SoftwareSerial.h>

#define PMTK_SET_NMEA_UPDATE_100_MILLIHERTZ  "$PMTK220,10000*2F"
#define PMTK_SET_NMEA_UPDATE_200_MILLIHERTZ  "$PMTK220,5000*1B"
#define PMTK_SET_NMEA_UPDATE_1HZ  "$PMTK220,1000*1F"
#define PMTK_SET_NMEA_UPDATE_5HZ  "$PMTK220,200*2C"
#define PMTK_SET_NMEA_UPDATE_10HZ "$PMTK220,100*2F"
#define PMTK_API_SET_FIX_CTL_100_MILLIHERTZ  "$PMTK300,10000,0,0,0,0*2C"
#define PMTK_API_SET_FIX_CTL_200_MILLIHERTZ  "$PMTK300,5000,0,0,0,0*18"
#define PMTK_API_SET_FIX_CTL_1HZ  "$PMTK300,1000,0,0,0,0*1C"
#define PMTK_API_SET_FIX_CTL_5HZ  "$PMTK300,200,0,0,0,0*2F"
#define PMTK_SET_BAUD_57600 "$PMTK251,57600*2C"
#define PMTK_SET_BAUD_9600 "$PMTK251,9600*17"
#define PMTK_SET_NMEA_OUTPUT_RMCONLY "$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29"
#define PMTK_SET_NMEA_OUTPUT_RMCGGA "$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28"
#define PMTK_SET_NMEA_OUTPUT_ALLDATA "$PMTK314,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0*28"
#define PMTK_SET_NMEA_OUTPUT_OFF "$PMTK314,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28"
#define PMTK_ENABLE_SBAS "$PMTK313,1*2E"
#define PMTK_ENABLE_WAAS "$PMTK301,2*2E"

#define GPS_START_DELIM         0x24    //$
#define GPS_CHKSUM_DELIM        0x2A    //*
#define GPS_ELEMENT_DELIM       0x2C    //,
#define GPS_STATUS_UNKNOWN      0x00
#define GPS_STATUS_ACTIVE       0x01
#define GPS_STATUS_VOID         0x02
#define GPS_MODE_UNKNOWN        0x00
#define GPS_MODE_AUTONOMOUS     0x01
#define GPS_MODE_DIFFERENTIAL   0x02
#define GPS_MODE_ESTIMATED      0x03
#define GPS_MODE_NOT_VALID      0x04
#define GPS_MODE_SIMULATOR      0x05

#define GPS_MS_INIT             0x00
#define GPS_MS_ERROR            0x01
#define GPS_MS_READY            0x02
#define GPS_MS_READING          0x03

#define GPS_STATUS_NODATA       0x01
#define GPS_STATUS_READING      0x02
#define GPS_STATUS_SUCCESS_GGA  0x03
#define GPS_STATUS_SUCCESS_RMC  0x04
#define GPS_STATUS_SUCCESS_OTH  0x05    //other, unsupported, setence
#define GPS_ERROR_CHECKSUM      0x10
#define GPS_ERROR_PARSE_ERR     0x20
#define GPS_ERROR_TIMEOUT       0x30


class GPS_MTK3339{
public:
    GPS_MTK3339(HardwareSerial* s);
    GPS_MTK3339(SoftwareSerial* s);
    
    uint8_t Read();
    void Send(const char* str);
    
    uint8_t Buffer[256];
    
    float    FixTime;
    uint8_t  FixQuality;
    uint8_t  Status;
    char     StatusChar;
    uint8_t  Mode;
    float    Longitude;
    float    Latitude;
    float    Altitude;
    float    Geoid;
    float    Precision;
    float    GroundSpeed;
    float    GroundTrack;
    float    MagneticVariation;
    
private:
    HardwareSerial* _hserial;
    SoftwareSerial* _sserial;
    bool _useSserial;
    
    uint8_t _machineState = GPS_MS_INIT;
    uint8_t _bufferOffset = 0;
    
    int serial_available(){
        if(_useSserial){ return _sserial->available(); }
        return _hserial->available();
    }
    int serial_read(){
        if(_useSserial){ return _sserial->read(); }
        return _hserial->read();
    }
    
    struct {
        float       fixTime;
        uint8_t     fixQuality;
        uint8_t     status;
        char        statusChar;
        uint8_t     mode;
        float       longitude;
        float       latitude;
        float       altitude;
        float       geoid;
        float       precision;
        float       groundSpeed;
        float       groundTrack;
        float       magneticVariation;
    } _tempValues;
    
    uint8_t startRead();
    uint8_t continueRead();
    void writeBuffer(uint8_t b);
    uint8_t parseSentence();
    uint8_t getsentenceName();
    bool parseRmc(uint8_t element, uint8_t start, uint8_t stop);
    bool parseGga(uint8_t element, uint8_t start, uint8_t stop);
    bool verifyChecksum(uint8_t start);
    void loadValues();
    
    float normalizeDegrees(float degrees);
};

#endif
