
/* Kernel includes. */
// #include "FreeRTOS.h"

// ssh ieeeupsb@192.168.0.162
// pass 1234

#include "Arduino.h"
#include "micro_controller_unit.h"

MicroControllerUnit &mcu = MicroControllerUnit::getInstance();

void setup() {
}

void loop() {
    mcu.test_motors();
}