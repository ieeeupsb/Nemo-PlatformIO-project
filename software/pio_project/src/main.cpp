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

double left_target_speed = 200;
double right_target_speed = 200;

void setup() {
    attachInterrupt(digitalPinToInterrupt(ENC_C1_PIN_L), updateLeftCount, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENC_C1_PIN_R), updateRightCount, CHANGE);

    // attachInterrupt(rising(ENC_C1_PIN_L), updateLeftCount, CHANGE);

    double Kp = 1;
    double Ki = 0;
    double Kd = 0;

    // left_motor_controller.pidSampleTime(5);

    left_motor_controller.SetPIDConstants(Kp, Ki, Kp);
    right_motor_controller.SetPIDConstants(Kp, Ki, Kp);

    left_motor_controller.setTargetSpeed(left_target_speed);
    right_motor_controller.setTargetSpeed(right_target_speed);

    Serial.begin(9600);
}
unsigned long last_time;

void loop() {

    // Serial.println(micros() - last_time);
    // Serial.println("micros() - last_time");
    // last_time = micros();

    double left_speed = left_motor_controller.updateSpeed();
    double right_speed = 0; // right_motor_controller.updateSpeed();
    // int left_pwm =
    // left_motor_controller.setPwm(255);

    // // // int right_pwm =
    int pwmL = left_motor_controller.setPidPwm();
    int pwmR = 0; // right_motor_controller.setPidPwm();

    // SerialSend(left_speed, right_speed);
    Serial.print(-left_speed);
    Serial.print(", ");
    Serial.print(pwmL);
    Serial.print(", ");
    Serial.print(right_speed);
    Serial.print(", ");
    Serial.println(pwmR);
}

// pio device monitor -p /dev/ttyACM0 > output.csv
