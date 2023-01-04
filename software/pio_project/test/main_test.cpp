
#define PICO

#include "motor_controller.h"
#include "pin_wiring.h"
// #include "serial_parser.h"

#define NON_BLOCKING_DELAY_MS(__DO_SOMETHING__, __WAIT_TIME_MS__) \
    {                                                             \
        static unsigned long last_time = 0;                       \
        if ((millis() - last_time) > __WAIT_TIME_MS__) {          \
            __DO_SOMETHING__;                                     \
            last_time = millis();                                 \
        }                                                         \
    }

long last_count = 0;
unsigned long lastReadTime = 0;

MotorController left_motor_controller = MotorController(ENC1_L, ENC2_L, ENABLE_L);
MotorController right_motor_controller = MotorController(ENC1_R, ENC2_R, ENABLE_L);

// Interrupt service routine
void InterruptHandler() {
    left_motor_controller.InterruptHandler();
    right_motor_controller.InterruptHandler();
}

void setup() {
    Serial.begin(BAUD_RATE);
}

#define WAIT_TIME_MS 1000

// int aux_print_motor_rpm() {
//     Serial.println(motor_controller.GetRpm());
// }

void loop() {

    int rpm;
    NON_BLOCKING_DELAY_MS(Serial.println(left_motor_controller.GetRpm());, WAIT_TIME_MS)
}

// alias smonitor="platformio device monitor --port /dev/ttyACM0 --baud 115200"

// char buffer[BUFFER_SIZE];
// void loop() {
//     SerialParser serial_parser;

//     if (millis() - lastReadTime > 1000) { // Only read from serial port every 1 second
//         // strcpy(buffer, serial_parser.ReadInput());
//         // Serial.print("BEGIN OF READ----");
//         // Serial.print(buffer);
//         // Serial.println("----END OF READ");<DIR:LEFT;DIST:0.5;SPEED:0.5>
//         serial_parser.GetCommand();

//         lastReadTime = millis();
//     }
// }
