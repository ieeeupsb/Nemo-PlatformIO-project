#include "Arduino.h"
#include "mcu_api.h"
#include "motion_controller.h"
#include "motor_controller.h"
#include "pin_wiring.h"
#include <PID_AutoTune_v0.h>
#include <PID_v1.h>

#define TIMER0_INTERVAL_MS 200

wheels_speed_t wheels_speed;
Robot &robot = Robot::getInstance();
McuAPI api(115200);

MotorController left_motor_controller(DRIVER_ENABLE_PIN_L, DRIVER_IN_A_PIN_L, DRIVER_IN_B_PIN_L, ENC_C1_PIN_L, ENC_C2_PIN_L, 0, 0, 0);
MotorController right_motor_controller(DRIVER_ENABLE_PIN_R, DRIVER_IN_A_PIN_R, DRIVER_IN_B_PIN_R, ENC_C1_PIN_R, ENC_C2_PIN_R, 0, 0, 0);

void updateLeftCount() {
    left_motor_controller.updateCount();
}

void updateRightCount() {
    right_motor_controller.updateCount();
}

void SerialSend(double left_speed, int left_pwm, double right_speed, int right_pwm) {
    Serial.print(left_speed);
    Serial.print(",");
    Serial.print(left_pwm);
    Serial.print(",");
    Serial.print(right_speed);
    Serial.print(",");
    Serial.println(right_pwm);
}

double left_target_speed = 200;
double right_target_speed = 200;

void setup() {
    attachInterrupt(digitalPinToInterrupt(ENC_C1_PIN_L), updateLeftCount, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENC_C1_PIN_R), updateRightCount, CHANGE);

    left_motor_controller.setTargetSpeed(left_target_speed);
    right_motor_controller.setTargetSpeed(right_target_speed);
    left_motor_controller.enablePidControl();
    right_motor_controller.enablePidControl();
}

int command_type;
double parameter_1;
double parameter_2;
double parameter_3;

void loop() {
    api.read();

    api.parseInputAndCreateCommand();

    if (0 != api.commandListSize()) {
        pico_command_t current_command = api.getNextCommand();

        command_type = (int)current_command.x;
        parameter_1 = current_command.y;
        parameter_2 = current_command.v;
        parameter_3 = current_command.w;
    }

    switch (command_type) {
    case 0:
        left_motor_controller.setTargetSpeed(robot.velocities_generator(-500, 0).left_wheel_speed);
        right_motor_controller.setTargetSpeed(robot.velocities_generator(500, 0).right_wheel_speed);
        break;

    case 1:
        left_motor_controller.SetPIDConstants(parameter_1, parameter_2, parameter_3);
    case 2:
        right_motor_controller.SetPIDConstants(parameter_1, parameter_2, parameter_3);

    default:
        break;
    }

    double left_speed = left_motor_controller.updateSpeed();
    int left_pwm = left_motor_controller.setPidPwm();

    double right_speed = right_motor_controller.updateSpeed();
    int right_pwm = right_motor_controller.setPidPwm();

    SerialSend(left_speed, left_pwm, right_speed, right_pwm);
}