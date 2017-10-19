#include "XBee2.h"

uint8_t RxPacket::Read(){
    #ifdef XBEE2_RX_DEBUG
        XBEE2_DEBUG_PRINTLN("xbee: read");
    #endif
    
    uint8_t offset = 0;
    memset(Packet.Array, 0, sizeof(Packet.Array));
    
    if(read(offset) == false){ return API_RXPACKET_NO_DATA_AVAILABLE; }
    Packet.Length = offset;
    
    #ifdef XBEE2_RX_DEBUG
        XBEE2_DEBUG_PRINT("RX BYTES IN ");
        for(uint8_t i = 0; i < Packet.Length; i++){
            XBEE2_DEBUG_PRINTBYTE(Packet.Array[i]);
        }
        XBEE2_DEBUG_PRINTLN("");
    #endif
    
    if(Packet.Length < API_RXPACKET_METADATA_LENGTH){
        #ifdef XBEE2_RX_DEBUG
            XBEE2_DEBUG_PRINTLN("xbee: length error");
        #endif
        return API_RXPACKET_READ_ERROR_LENGTH;
    }
    if(Packet.Array[FRAME_TYPE_OFFSET] != FrameType){
        #ifdef XBEE2_RX_DEBUG
            XBEE2_DEBUG_PRINTLN("xbee: frame type error");
        #endif
        return API_RXPACKET_READ_ERROR_FRAME_TYPE;
    }
    
    PayloadLength =  Convert.getInt16(Packet.Array, LENGTH_MSB_OFFSET);
    uint8_t checksum = calcChecksum(Packet.Array, FRAME_TYPE_OFFSET, PayloadLength);
    if(checksum != Packet.Array[offset - 1]){
        #ifdef XBEE2_RX_DEBUG
            XBEE2_DEBUG_PRINT("xbee: checksum error - expected: ");
            XBEE2_DEBUG_PRINTBYTE(Packet.Array[offset - 1]);
            XBEE2_DEBUG_PRINT("found: ");
            XBEE2_DEBUG_PRINTBYTE(checksum);
            XBEE2_DEBUG_PRINTLN("");
        #endif
        return API_RXPACKET_READ_ERROR_CHECKSUM;
    }
    
    LongAddress =  Convert.getInt64(Packet.Array, API_RXPACKET_LONGADDRESS_OFFSET);
    ShortAddress =  Convert.getInt16(Packet.Array, API_RXPACKET_SHORTADDRESS_OFFSET);
    Options = Packet.Array[API_RXPACKET_OPTIONS_OFFSET];
    
    PayloadLength = Packet.Length - API_RXPACKET_OVERHEAD_LENGTH;
    for(uint8_t i = 0; i < PayloadLength; i++){
        Payload[i] = Packet.Array[API_RXPACKET_PAYLOAD_OFFSET + i];
    }
    
    #ifdef XBEE2_RX_DEBUG
        XBEE2_DEBUG_PRINT("xbee: returning "); XBEE2_DEBUG_PRINTLN(API_RXPACKET_READ_SUCCESS);
    #endif
    
    return API_RXPACKET_READ_SUCCESS;
}

