#include "XBee2.h"
#include "XBee2_defines.h"

void TxRequest::Write(uint8_t *buffer, uint8_t length, bool useEndToEndSecuirty, uint8_t frameId) {
    Packet.Array[START_DELIMITER_OFFSET] = START_DELIMITER;
    Packet.Array[FRAME_TYPE_OFFSET] = FrameType;
    Packet.Array[FRAME_ID_OFFSET] = frameId;
    Convert.getBytes(LongAddress, Packet.Array, API_TXREQUEST_LONGADDRESS_OFFSET);
    Convert.getBytes(ShortAddress, Packet.Array, API_TXREQUEST_SHORTADDRESS_OFFSET);
    Packet.Array[API_TXREQUEST_RADIUS_OFFSET] = RadiusOffset;
    
    uint8_t opts = Options;
    if(useEndToEndSecuirty){ opts |= 0x20; }
    Packet.Array[API_TXREQUEST_OPTIONS_OFFSET] = opts;
    
    for(int i = 0; i < length; i++){
        Packet.Array[API_TXREQUEST_PAYLOAD_OFFSET + i] = buffer[i];
    }
    
    length = API_TXREQUEST_OVERHEAD_LENGTH + length;
    Packet.Length = length;
    int payloadLength = length - API_TXREQUEST_ENVELOPE_LENGTH;
    
    Packet.Array[LENGTH_MSB_OFFSET] = (byte)(payloadLength >> 8);
    Packet.Array[LENGTH_LSB_OFFSET] = (byte)payloadLength;
    
    Packet.Array[length - 1] = calcChecksum(Packet.Array, FRAME_TYPE_OFFSET, payloadLength);
    
    #ifdef XBEE2_TX_DEBUG
        //Packet.Array[length - 1]--;
        //XBEE2_DEBUG_PRINTBYTE(Packet.Array[length - 1]); XBEE2_DEBUG_PRINTLN("");
    #endif
    
    write();
    
    #ifdef XBEE2_TX_DEBUG
        XBEE2_DEBUG_PRINTLN("");
    #endif
}

