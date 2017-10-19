#include <ByteConverterLib.h>

uint8_t buffer[8] {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
void setup(){
    Serial.begin(9600);
    
    //floatTests();
    //int16Tests();
    //int32Tests();
    int64Tests();
}

void loop() {
}

void floatTests(){
    float test = 123.456;
    float test2;
    
    Serial.println("================================");
    Serial.println("FLOAT TESTS: ");
    Serial.println("================================");
    
    //
    //TEST 1
    //
    Serial.println("basic conversion: ");
    Serial.print("value to convert: ");
    Serial.println(test, 4);
    
    clearBuffer();
    Convert.getBytes(test, buffer, 0);
    
    Serial.print("buffer values: ");
    for(uint8_t i = 0; i < sizeof(buffer); i++){
        printByte(buffer[i]);
    }
    Serial.println();
    
    test2 = Convert.getFloat(buffer, 0);
    
    Serial.print("value recovered from buffer: ");
    Serial.println(test2, 4);
    
    //
    //TEST 2
    //
    Serial.println("--------------------------------");
    Serial.println("lsb first test: ");
    
    Serial.print("value to convert: ");
    Serial.println(test, 4);
    
    clearBuffer();
    Convert.getBytes(test, buffer, false);
    
    Serial.print("buffer values: ");
    for(uint8_t i = 0; i < sizeof(buffer); i++){
        printByte(buffer[i]);
    }
    Serial.println();
    
    test2 = Convert.getFloat(buffer, false);
    
    Serial.print("value recovered from buffer: ");
    Serial.println(test2, 4);
    
    //
    //TEST 3
    //
    Serial.println("--------------------------------");
    Serial.println("buffer offset test: ");
    
    Serial.print("value to convert: ");
    Serial.println(test, 4);
    
    clearBuffer();
    Convert.getBytes(test, buffer, 4);
    
    Serial.print("buffer values: ");
    for(uint8_t i = 0; i < sizeof(buffer); i++){
        printByte(buffer[i]);
    }
    Serial.println();
    
    test2 = Convert.getFloat(buffer, 4);
    
    Serial.print("value recovered from buffer: ");
    Serial.println(test2, 4);
    
    //
    //TEST 4
    //
    Serial.println("--------------------------------");
    Serial.println("buffer offset & lsb first test: ");
    
    Serial.print("value to convert: ");
    Serial.println(test, 4);
    
    clearBuffer();
    Convert.getBytes(test, buffer, 4, false);
    
    Serial.print("buffer values: ");
    for(uint8_t i = 0; i < sizeof(buffer); i++){
        printByte(buffer[i]);
    }
    Serial.println();
    
    test2 = Convert.getFloat(buffer, 4, false);
    
    Serial.print("value recovered from buffer: ");
    Serial.println(test2, 4);
}

void int16Tests(){
    uint16_t test = 12345;
    uint16_t test2;
    
    Serial.println("================================");
    Serial.println("UNSIGNED INT16 TESTS: ");
    Serial.println("================================");
    
    //
    //TEST 1
    //
    Serial.println("basic conversion: ");
    Serial.print("value to convert: ");
    Serial.println(test, HEX);
    
    clearBuffer();
    Convert.getBytes(test, buffer, 0);
    
    Serial.print("buffer values: ");
    for(uint8_t i = 0; i < sizeof(buffer); i++){
        printByte(buffer[i]);
    }
    Serial.println();
    
    test2 = Convert.getUInt16(buffer, 0);
    
    Serial.print("value recovered from buffer: ");
    Serial.println(test2, HEX);
    
    //
    //TEST 2
    //
    Serial.println("--------------------------------");
    Serial.println("lsb first test: ");
    
    Serial.print("value to convert: ");
    Serial.println(test, HEX);
    
    clearBuffer();
    Convert.getBytes(test, buffer, 0, false);
    
    Serial.print("buffer values: ");
    for(uint8_t i = 0; i < sizeof(buffer); i++){
        printByte(buffer[i]);
    }
    Serial.println();
    
    test2 = Convert.getUInt16(buffer, 0, false);
    
    Serial.print("value recovered from buffer: ");
    Serial.println(test2, HEX);
    
    //
    //TEST 3
    //
    Serial.println("--------------------------------");
    Serial.println("buffer offset test: ");
    
    Serial.print("value to convert: ");
    Serial.println(test, HEX);
    
    clearBuffer();
    Convert.getBytes(test, buffer, 4);
    
    Serial.print("buffer values: ");
    for(uint8_t i = 0; i < sizeof(buffer); i++){
        printByte(buffer[i]);
    }
    Serial.println();
    
    test2 = Convert.getUInt16(buffer, 4);
    
    Serial.print("value recovered from buffer: ");
    Serial.println(test2, HEX);
    
    //
    //TEST 4
    //
    Serial.println("--------------------------------");
    Serial.println("buffer offset & lsb first test: ");
    
    Serial.print("value to convert: ");
    Serial.println(test, HEX);
    
    clearBuffer();
    Convert.getBytes(test, buffer, 4, false);
    
    Serial.print("buffer values: ");
    for(uint8_t i = 0; i < sizeof(buffer); i++){
        printByte(buffer[i]);
    }
    Serial.println();
    
    test2 = Convert.getUInt16(buffer, 4, false);
    
    Serial.print("value recovered from buffer: ");
    Serial.println(test2, HEX);
    
    
    Serial.println("================================");
    Serial.println("INT16 TESTS: ");
    Serial.println("================================");
    
    int16_t test3 = -12345;
    int16_t test4;
    
    //
    //TEST 5
    //
    Serial.println("basic conversion: ");
    
    Serial.print("value to convert: ");
    Serial.print(test3); Serial.print("\t");
    Serial.println(test3, HEX);
    
    clearBuffer();
    Convert.getBytes(test3, buffer, 0);
    
    Serial.print("buffer values: ");
    for(uint8_t i = 0; i < sizeof(buffer); i++){
        printByte(buffer[i]);
    }
    Serial.println();
    
    test4 = Convert.getUInt16(buffer, 0);
    
    Serial.print("value recovered from buffer: ");
    Serial.print(test4); Serial.print("\t");
    Serial.println(test4, HEX);
    
    //
    //TEST 6
    //
    Serial.println("--------------------------------");
    Serial.println("lsb first test: ");
    
    Serial.print("value to convert: ");
    Serial.print(test3); Serial.print("\t");
    Serial.println(test3, HEX);
    
    clearBuffer();
    Convert.getBytes(test3, buffer, 0, false);
    
    Serial.print("buffer values: ");
    for(uint8_t i = 0; i < sizeof(buffer); i++){
        printByte(buffer[i]);
    }
    Serial.println();
    
    test4 = Convert.getUInt16(buffer, 0, false);
    
    Serial.print("value recovered from buffer: ");
    Serial.print(test4); Serial.print("\t");
    Serial.println(test4, HEX);
    
    //
    //TEST 7
    //
    Serial.println("--------------------------------");
    Serial.println("buffer offset test: ");
    
    Serial.print("value to convert: ");
    Serial.print(test3); Serial.print("\t");
    Serial.println(test3, HEX);
    
    clearBuffer();
    Convert.getBytes(test3, buffer, 4);
    
    Serial.print("buffer values: ");
    for(uint8_t i = 0; i < sizeof(buffer); i++){
        printByte(buffer[i]);
    }
    Serial.println();
    
    test4 = Convert.getUInt16(buffer, 4);
    
    Serial.print("value recovered from buffer: ");
    Serial.print(test4); Serial.print("\t");
    Serial.println(test4, HEX);
    
    //
    //TEST 8
    //
    Serial.println("--------------------------------");
    Serial.println("buffer offset & lsb first test: ");
    
    Serial.print("value to convert: ");
    Serial.print(test3); Serial.print("\t");
    Serial.println(test3, HEX);
    
    clearBuffer();
    Convert.getBytes(test3, buffer, 4, false);
    
    Serial.print("buffer values: ");
    for(uint8_t i = 0; i < sizeof(buffer); i++){
        printByte(buffer[i]);
    }
    Serial.println();
    
    test4 = Convert.getUInt16(buffer, 4, false);
    
    Serial.print("value recovered from buffer: ");
    Serial.print(test4); Serial.print("\t");
    Serial.println(test4, HEX);
}

void int32Tests(){
    uint32_t test = 1234512345;
    uint32_t test2;
    
    Serial.println("================================");
    Serial.println("UNSIGNED INT32 TESTS: ");
    Serial.println("================================");
    
    //
    //TEST 1
    //
    Serial.println("basic conversion: ");
    Serial.print("value to convert: ");
    Serial.print(test); Serial.print("\t");
    Serial.println(test, HEX);
    
    clearBuffer();
    Convert.getBytes(test, buffer, 0);
    
    Serial.print("buffer values: ");
    for(uint8_t i = 0; i < sizeof(buffer); i++){
        printByte(buffer[i]);
    }
    Serial.println();
    
    test2 = Convert.getUInt32(buffer, 0);
    
    Serial.print("value recovered from buffer: ");
    Serial.print(test2); Serial.print("\t");
    Serial.println(test2, HEX);
    
    //
    //TEST 2
    //
    Serial.println("--------------------------------");
    Serial.println("lsb first test: ");
    
    Serial.print("value to convert: ");
    Serial.print(test); Serial.print("\t");
    Serial.println(test, HEX);
    
    clearBuffer();
    Convert.getBytes(test, buffer, 0, false);
    
    Serial.print("buffer values: ");
    for(uint8_t i = 0; i < sizeof(buffer); i++){
        printByte(buffer[i]);
    }
    Serial.println();
    
    test2 = Convert.getUInt32(buffer, 0, false);
    
    Serial.print("value recovered from buffer: ");
    Serial.print(test2); Serial.print("\t");
    Serial.println(test2, HEX);
    
    //
    //TEST 3
    //
    Serial.println("--------------------------------");
    Serial.println("buffer offset test: ");
    
    Serial.print("value to convert: ");
    Serial.print(test); Serial.print("\t");
    Serial.println(test, HEX);
    
    clearBuffer();
    Convert.getBytes(test, buffer, 4);
    
    Serial.print("buffer values: ");
    for(uint8_t i = 0; i < sizeof(buffer); i++){
        printByte(buffer[i]);
    }
    Serial.println();
    
    test2 = Convert.getUInt32(buffer, 4);
    
    Serial.print("value recovered from buffer: ");
    Serial.print(test2); Serial.print("\t");
    Serial.println(test2, HEX);
    
    //
    //TEST 4
    //
    Serial.println("--------------------------------");
    Serial.println("buffer offset & lsb first test: ");
    
    Serial.print("value to convert: ");
    Serial.print(test); Serial.print("\t");
    Serial.println(test, HEX);
    
    clearBuffer();
    Convert.getBytes(test, buffer, 4, false);
    
    Serial.print("buffer values: ");
    for(uint8_t i = 0; i < sizeof(buffer); i++){
        printByte(buffer[i]);
    }
    Serial.println();
    
    test2 = Convert.getUInt32(buffer, 4, false);
    
    Serial.print("value recovered from buffer: ");
    Serial.print(test2); Serial.print("\t");
    Serial.println(test2, HEX);
    
    
    Serial.println("================================");
    Serial.println("INT32 TESTS: ");
    Serial.println("================================");
    
    int32_t test3 = -1234512345;
    int32_t test4;
    
    //
    //TEST 5
    //
    Serial.println("basic conversion: ");
    
    Serial.print("value to convert: ");
    Serial.print(test3); Serial.print("\t");
    Serial.println(test3, HEX);
    
    clearBuffer();
    Convert.getBytes(test3, buffer, 0);
    
    Serial.print("buffer values: ");
    for(uint8_t i = 0; i < sizeof(buffer); i++){
        printByte(buffer[i]);
    }
    Serial.println();
    
    test4 = Convert.getUInt32(buffer, 0);
    
    Serial.print("value recovered from buffer: ");
    Serial.print(test4); Serial.print("\t");
    Serial.println(test4, HEX);
    
    //
    //TEST 6
    //
    Serial.println("--------------------------------");
    Serial.println("lsb first test: ");
    
    Serial.print("value to convert: ");
    Serial.print(test3); Serial.print("\t");
    Serial.println(test3, HEX);
    
    clearBuffer();
    Convert.getBytes(test3, buffer, 0, false);
    
    Serial.print("buffer values: ");
    for(uint8_t i = 0; i < sizeof(buffer); i++){
        printByte(buffer[i]);
    }
    Serial.println();
    
    test4 = Convert.getUInt32(buffer, 0, false);
    
    Serial.print("value recovered from buffer: ");
    Serial.print(test4); Serial.print("\t");
    Serial.println(test4, HEX);
    
    //
    //TEST 7
    //
    Serial.println("--------------------------------");
    Serial.println("buffer offset test: ");
    
    Serial.print("value to convert: ");
    Serial.print(test3); Serial.print("\t");
    Serial.println(test3, HEX);
    
    clearBuffer();
    Convert.getBytes(test3, buffer, 4);
    
    Serial.print("buffer values: ");
    for(uint8_t i = 0; i < sizeof(buffer); i++){
        printByte(buffer[i]);
    }
    Serial.println();
    
    test4 = Convert.getUInt32(buffer, 4);
    
    Serial.print("value recovered from buffer: ");
    Serial.print(test4); Serial.print("\t");
    Serial.println(test4, HEX);
    
    //
    //TEST 8
    //
    Serial.println("--------------------------------");
    Serial.println("buffer offset & lsb first test: ");
    
    Serial.print("value to convert: ");
    Serial.print(test3); Serial.print("\t");
    Serial.println(test3, HEX);
    
    clearBuffer();
    Convert.getBytes(test3, buffer, 4, false);
    
    Serial.print("buffer values: ");
    for(uint8_t i = 0; i < sizeof(buffer); i++){
        printByte(buffer[i]);
    }
    Serial.println();
    
    test4 = Convert.getUInt32(buffer, 4, false);
    
    Serial.print("value recovered from buffer: ");
    Serial.print(test4); Serial.print("\t");
    Serial.println(test4, HEX);
}

void int64Tests(){
    uint64_t test = 0x0123456789ABCDEF;
    
    Serial.println("================================");
    Serial.println("UNSIGNED INT64 TESTS: ");
    Serial.println("================================");
    
    //
    //TEST 1
    //
    Serial.println("basic conversion: ");
    
    clearBuffer();
    Convert.getBytes(test, buffer, 0);
    
    Serial.print("buffer values: ");
    for(uint8_t i = 0; i < sizeof(buffer); i++){
        printByte(buffer[i]);
    }
    Serial.println();
    
    //
    //TEST 2
    //
    Serial.println("--------------------------------");
    Serial.println("lsb first test: ");
    
    clearBuffer();
    Convert.getBytes(test, buffer, 0, false);
    
    Serial.print("buffer values: ");
    for(uint8_t i = 0; i < sizeof(buffer); i++){
        printByte(buffer[i]);
    }
    Serial.println();
    
    
    Serial.println("================================");
    Serial.println("INT64 TESTS: ");
    Serial.println("================================");
    
    int64_t test3 = 0x8123456789ABCDEF;
    
    //
    //TEST 3
    //
    Serial.println("basic conversion: ");
    
    clearBuffer();
    Convert.getBytes(test3, buffer, 0);
    
    Serial.print("buffer values: ");
    for(uint8_t i = 0; i < sizeof(buffer); i++){
        printByte(buffer[i]);
    }
    Serial.println();
    
    //
    //TEST 4
    //
    Serial.println("--------------------------------");
    Serial.println("lsb first test: ");
    
    clearBuffer();
    Convert.getBytes(test3, buffer, 0, false);
    
    Serial.print("buffer values: ");
    for(uint8_t i = 0; i < sizeof(buffer); i++){
        printByte(buffer[i]);
    }
    Serial.println();
}

void clearBuffer(){
    memset(buffer, 0, sizeof(buffer));
}

void printByte(uint8_t b){
    Serial.print("0x");
    if(b < 0x10) { Serial.print("0"); }
    Serial.print(b, HEX);
    Serial.print(" ");
}

