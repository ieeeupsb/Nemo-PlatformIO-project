#include "Arduino.h"
#include "mcu_api.h"
#include "motor_controller.h"
#include "pin_wiring.h"
#include "robot.h"
#include <PID_AutoTune_v0.h>
#include <PID_v1.h>

#define TIMER0_INTERVAL_MS 200
#define MAX_COMMAND_FAILED 10

wheels_speed_t wheels_speed;
Robot &robot = Robot::getInstance();

MotorController left_motor_controller(DRIVER_ENABLE_PIN_L, DRIVER_IN_A_PIN_L, DRIVER_IN_B_PIN_L, ENC_C1_PIN_L, ENC_C2_PIN_L, 0.2, 1, 0);
MotorController right_motor_controller(DRIVER_ENABLE_PIN_R, DRIVER_IN_A_PIN_R, DRIVER_IN_B_PIN_R, ENC_C1_PIN_R, ENC_C2_PIN_R, 0.2, 1, 0);

void updateLeftCount() {
    left_motor_controller.updateCount();
}

void updateRightCount() {
    right_motor_controller.updateCount();
}

void SerialSend(double left_speed, int left_pwm, double right_speed, int right_pwm) {
    Serial.print(left_speed / 1);
    // 3846
    Serial.print(",");
    Serial.print(left_pwm);
    Serial.print(",");
    Serial.print(right_speed / 1);
    Serial.print(",");
    Serial.println(right_pwm);
}

double left_target_speed = 0;
double right_target_speed = 0;

void setup() {
    Serial.begin(115200);
    attachInterrupt(digitalPinToInterrupt(ENC_C1_PIN_L), updateLeftCount, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENC_C1_PIN_R), updateRightCount, CHANGE);

    // pinMode(ELETROMAGNET_PIN, OUTPUT);

    left_motor_controller.setTargetSpeed(left_target_speed);
    right_motor_controller.setTargetSpeed(right_target_speed);
    left_motor_controller.enablePidControl();
    right_motor_controller.enablePidControl();
}

bool getParameters(String incoming, int *command_type, double *parameter1, double *parameter2, double *parameter3) {

    static int error_counting = 0;

    int x_index = incoming.indexOf("x:");
    int y_index = incoming.indexOf("y:");
    int v_index = incoming.indexOf("v:");
    int w_index = incoming.indexOf("w:");

    if (x_index == -1 || y_index == -1 || v_index == -1 || w_index == -1) {

        if (error_counting > MAX_FAILED_COMMANDS) {

            Serial.end();
        }

        return false;
    }

    int semi_colon_index = 0;
    error_counting = 0;

    semi_colon_index = incoming.indexOf(";");
    String x_substring = incoming.substring(2, semi_colon_index);
    incoming = incoming.substring(semi_colon_index + 1);

    semi_colon_index = incoming.indexOf(";");
    String y_substring = incoming.substring(2, semi_colon_index);
    incoming = incoming.substring(semi_colon_index + 1);

    semi_colon_index = incoming.indexOf(";");
    String v_substring = incoming.substring(2, semi_colon_index);
    incoming = incoming.substring(semi_colon_index + 1);

    String w_substring = incoming.substring(2);

    *command_type = x_substring.toInt();
    *parameter1 = y_substring.toDouble();
    *parameter2 = v_substring.toDouble() / 3846;
    *parameter3 = w_substring.toDouble();

    return true;
}

int command_type = 0;
double parameter_1 = 0;
double parameter_2 = 0;
double parameter_3 = 0;

void loop() {
    String incoming;

    while (Serial.available()) {
        delay(2);
        char c = Serial.read();
        incoming += c;
    }
    getParameters(incoming, &command_type, &parameter_1, &parameter_2, &parameter_3);
    Serial.println(incoming);

    // command_type = 0;
    // parameter_2 = 2000;
    // parameter_3 = 0;

    switch (command_type) {
    case 0:
        left_motor_controller.setTargetSpeed(robot.velocities_generator(parameter_2, parameter_3).left_wheel_speed);
        right_motor_controller.setTargetSpeed(robot.velocities_generator(parameter_2, parameter_3).right_wheel_speed);
        break;

    case 1:
        left_motor_controller.SetPIDConstants(parameter_1, parameter_2, parameter_3);
        break;
    case 2:
        right_motor_controller.SetPIDConstants(parameter_1, parameter_2, parameter_3);
        break;
    case 3:
        digitalWrite(ELETROMAGNET_PIN, int(parameter_1));
        break;

    default:
        break;
    }

    double left_speed = left_motor_controller.updateSpeed();
    int left_pwm = left_motor_controller.setPidPwm();

    double right_speed = right_motor_controller.updateSpeed();
    int right_pwm = right_motor_controller.setPidPwm();

    // SerialSend(left_speed, left_pwm, right_speed, right_pwm);
}