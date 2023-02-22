
/* Kernel includes. */
// #include "FreeRTOS.h"

// ssh ieeeupsb@192.168.0.162
// pass 1234

#include "Arduino.h"
#include "motion_controller.h"
#include "motor_controller.h"
#include "pin_wiring.h"
#include <PID_AutoTune_v0.h>
#include <PID_v1.h>

// Robot &robot = Robot::getInstance();

MotorController left_motor_controller(DRIVER_ENABLE_PIN_L, DRIVER_IN_A_PIN_L, DRIVER_IN_B_PIN_L, ENC_C1_PIN_L, ENC_C2_PIN_L, 0, 0, 0);
MotorController right_motor_controller(DRIVER_ENABLE_PIN_R, DRIVER_IN_A_PIN_R, DRIVER_IN_B_PIN_R, ENC_C1_PIN_R, ENC_C2_PIN_R, 0, 0, 0);

void updateLeftCount() {
    left_motor_controller.updateCount();
}

void updateRightCount() {
    right_motor_controller.updateCount();
}

void SerialSend(double left_speed, double right_speed) {

    static unsigned long last_time_ms = 0;
    const static unsigned long interval = 200;
    unsigned long current_time_ms = millis();

    if (current_time_ms - last_time_ms >= interval) {

        Serial.print(left_speed);
        // Serial.print(",");
        // Serial.println(right_speed);
        Serial.println("");

        last_time_ms = current_time_ms;
    }
}

void speedUpdater() {
}

void setup() {
    // attachInterrupt(digitalPinToInterrupt(ENC_C1_PIN_L), updateLeftCount, CHANGE);
    // attachInterrupt(digitalPinToInterrupt(ENC_C1_PIN_R), updateRightCount, CHANGE);

    // attachInterrupt(rising(ENC_C1_PIN_L), updateLeftCount, CHANGE);

    // double Kp = 0.3 * 0.6;
    // double Ki = 0.5;
    // double Kd = 0;

    // left_motor_controller.SetPIDConstants(Kp, Ki, Kp);
    // right_motor_controller.SetPIDConstants(Kp, Ki, Kp);

    // left_motor_controller.setTargetSpeed(left_target_speed);
    // right_motor_controller.setTargetSpeed(right_target_speed);

    Serial.begin(9600);
}

float angle_of_curve = 0;
float average_pmw = 122;
float tune_factor = 1;

void loop() {

    // angle_of_curve = <- UPDATE ANGLE
    left_motor_controller.setPwm(average_pwm + average_pwm * sin(angle) * tune_factor);
    right_motor_controller.setPwm(average_pwm - average_pwm * sin(angle) * tune_factor);
}

// pio device monitor -p /dev/ttyACM0 > output.csv
