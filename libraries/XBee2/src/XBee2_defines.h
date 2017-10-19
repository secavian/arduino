#ifndef _xbee2_defines_h_
#define _xbee2_defines_h_

#include "Arduino.h"
#include <SoftwareSerial.h>
#include <ByteConverterLib.h>

//ALL FRAMES HAVE THE SAME START DELIMITER BYTE VALUE
static const uint8_t START_DELIMITER                    = 0x7E;

//default addresses
static const uint64_t CONTROLLER_64BIT_ADDRESS                      = 0x0000000000000000;
static const uint64_t BROADCAST_64BIT_ADDRESS                       = 0x000000000000FFFF;
static const uint16_t DESTINATION_16BIT_NETWORK_ADDRESS_UNKNOWN     = 0xFFFE;
static const uint16_t DESTINATION_16BIT_NETWORK_ADDRESS_BROADCAST   = 0xFFFE;

/*  metadata offsets into the packet buffer used to assemble data read
    to or received from xbee module
*/

//ALL FRAMES HAVE THESE OFFSETS (4 BYTES TOTAL)
static const uint8_t START_DELIMITER_OFFSET             = 0;
static const uint8_t LENGTH_MSB_OFFSET                  = 1;
static const uint8_t LENGTH_LSB_OFFSET                  = 2;
static const uint8_t FRAME_TYPE_OFFSET                  = 3;

//FRAMES THAT HAVE A FRAME ID BYTE ALWAYS HAVE THIS OFFSET
static const uint8_t FRAME_ID_OFFSET                    = 4;

//envelope field sizes
static const uint8_t API_TXREQUEST_HEADER_LENGTH        = 3;    //Start delimiter(1) and length(2) bytes
static const uint8_t API_TXREQUEST_METADATA_LENGTH      = 14;   //Frame type(1), frame id(1), long address(8),
                                                                //short address(2), radius(1) and options(1) bytes
static const uint8_t API_TXREQUEST_CHECKSUM_LENGTH      = 1;    //Checksum byte
static const uint8_t API_TXREQUEST_OVERHEAD_LENGTH      = 18;   //HEADER_LENGTH + METADATA_LENGTH + CHECKSUM_LENGTH
static const uint8_t API_TXREQUEST_ENVELOPE_LENGTH      = 4;    //HEADER_LENGTH + CHECKSUM_LENGTH

static const uint8_t API_RXPACKET_HEADER_LENGTH         = 3;    //Start delimiter(1) and length(2) bytes
static const uint8_t API_RXPACKET_METADATA_LENGTH       = 12;   //Frame type(1), long address(8), short address(2),
                                                                //options(1) bytes
static const uint8_t API_RXPACKET_CHECKSUM_LENGTH       = 1;    //Checksum byte
static const uint8_t API_RXPACKET_OVERHEAD_LENGTH       = 16;   //HEADER_LENGTH + METADATA_LENGTH + CHECKSUM_LENGTH

//buffer offsets
static const uint8_t API_TXREQUEST_LONGADDRESS_OFFSET   = 5;
static const uint8_t API_TXREQUEST_SHORTADDRESS_OFFSET  = 13;
static const uint8_t API_TXREQUEST_RADIUS_OFFSET        = 15;
static const uint8_t API_TXREQUEST_OPTIONS_OFFSET       = 16;
static const uint8_t API_TXREQUEST_PAYLOAD_OFFSET       = 17;

static const uint8_t API_RXPACKET_LONGADDRESS_OFFSET    = 4;
static const uint8_t API_RXPACKET_SHORTADDRESS_OFFSET   = 12;
static const uint8_t API_RXPACKET_OPTIONS_OFFSET        = 14;
static const uint8_t API_RXPACKET_PAYLOAD_OFFSET        = 15;

//options
static const uint8_t API_RXPACKET_OPTIONS_PACKET_ACKNOWLEDGED   = 0x01;
static const uint8_t API_RXPACKET_OPTIONS_BROADCAST             = 0x02;
static const uint8_t API_RXPACKET_OPTIONS_ENCRYPTED             = 0x20;
static const uint8_t API_RXPACKET_OPTIONS_SENT_FROM_END_DEVICE  = 0x40;

//read results
static const uint8_t API_RXPACKET_READ_SUCCESS                  = 0;
static const uint8_t API_RXPACKET_NO_DATA_AVAILABLE             = 1;
static const uint8_t API_RXPACKET_READ_ERROR                    = 2;
static const uint8_t API_RXPACKET_READ_ERROR_LENGTH             = 3;
static const uint8_t API_RXPACKET_READ_ERROR_FRAME_TYPE         = 4;
static const uint8_t API_RXPACKET_READ_ERROR_CHECKSUM           = 5;
static const uint8_t API_RXPACKET_READ_ERROR_OTHER              = 0xFE;

#endif
