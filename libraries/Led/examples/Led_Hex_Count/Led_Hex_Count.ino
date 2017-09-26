#include <Led.h>

Led led0(8);
Led led1(9);
Led led2(10);
Led led3(11);

void setup() {
}

uint8_t value;

void loop() {
    value++;
    led0.OnWhen(value & 0x08);
    led1.OnWhen(value & 0x04);
    led2.OnWhen(value & 0x02);
    led3.OnWhen(value & 0x01);
    delay(250);
}
