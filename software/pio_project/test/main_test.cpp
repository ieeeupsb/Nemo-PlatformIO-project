
#define PICO

#include "motor_controller.h"
#include "pin_wiring.h"
#include "serial_parser.h"

long last_count = 0;
char buffer[BUFFER_SIZE];
unsigned long lastReadTime = 0;

MotorController motor_controller = MotorController(ENC1_L, ENC2_L, ENABLE_L);

// Interrupt service routine
void InterruptHandler() {
    // Update the encoder count
    motor_controller.InterruptHandler();
    // encoder.Update();
}

void setup() {
    Serial.begin(BAUD_RATE);
    // attachInterrupt(digitalPinToInterrupt(ENC1_L), InterruptHandler, CHANGE);
}

void loop() {
    SerialParser serial_parser;

    if (millis() - lastReadTime > 1000) { // Only read from serial port every 1 second
        // strcpy(buffer, serial_parser.ReadInput());
        // Serial.print("BEGIN OF READ----");
        // Serial.print(buffer);
        // Serial.println("----END OF READ");<DIR:LEFT;DIST:0.5;SPEED:0.5>
        serial_parser.GetCommand();

        lastReadTime = millis();
    }
}