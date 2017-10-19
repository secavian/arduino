#include <Led.h>
#include <BNO055.h>

Led redLed(5);
Led systemLed(13);

BNO055 bno;

void setup() {
    Serial.begin(115200);
    delay(1000);
    
    Serial.println("begin imu");
    if(bno.begin(IMU_OPERATION_MODE_NDOF) != IMU_ERROR_NONE){
        redLed.On();
        while(true){
            Serial.print("IMU ERROR: ");
            Serial.println(bno.errorCode);
            delay(1000);
        }
    }
}

void loop(){
    uint8_t r = bno.read();
    
    //if '*' displayed, then sensor read. otherwise, using unchanged values
    Serial.print(r == IMU_STATUS_SUCCESS ? "*" : " ");
    Serial.print("\theading: ");Serial.print(bno.heading);
    Serial.print("\tpitch:   ");Serial.print(bno.pitch);
    Serial.print("\troll:    ");Serial.print(bno.roll);
    Serial.println();
    
    if(r == IMU_STATUS_SUCCESS){
        systemLed.Toggle();
    }
    
    delay(5);
}


