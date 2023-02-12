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

byte ATuneModeRemember = 2;
double input = 80, output = 50, setpoint = 180;
double kp = 2, ki = 0.5, kd = 2;

double kpmodel = 1.5, taup = 100, theta[50];
double outputStart = 5;
double aTuneStep = 50, aTuneNoise = 1, aTuneStartValue = 100;
unsigned int aTuneLookBack = 20;

boolean tuning = false;
unsigned long modelTime, serialTime;

MotorController left_motor_controller(DRIVER_ENABLE_PIN_L, DRIVER_IN_A_PIN_L, DRIVER_IN_B_PIN_L, ENC_C1_PIN_L, ENC_C2_PIN_L, kp, ki, kd);
MotorController right_motor_controller(DRIVER_ENABLE_PIN_R, DRIVER_IN_A_PIN_R, DRIVER_IN_B_PIN_R, ENC_C1_PIN_R, ENC_C2_PIN_R, kp, ki, kd);

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

    left_motor_controller.SetPIDConstants(300 * 0.7, 158, 0);
    right_motor_controller.SetPIDConstants(325 * 0.7, 158, 0);

    left_motor_controller.setTargetSpeed(left_target_speed);
    right_motor_controller.setTargetSpeed(right_target_speed);
    left_motor_controller.enablePidControl();
    right_motor_controller.enablePidControl();

    serialTime = 0;
}
unsigned long last_time;

unsigned long last_time_ms;
double current_x;
double current_y;
double current_v;
double current_w;

void loop() {
    // if (millis() - last_time_ms >= 200) {
    api.read();

    //     last_time_ms = millis();
    // }

    api.parseInputAndCreateCommand();

    if (0 != api.commandListSize()) {
        pico_command_t current_command = api.getNextCommand();

        current_x = current_command.x;
        current_y = current_command.y;
        current_v = current_command.v;
        current_w = current_command.w;
    }

    left_motor_controller.setTargetSpeed(-robot.velocities_generator(current_v, current_w).left_wheel_speed);
    right_motor_controller.setTargetSpeed(robot.velocities_generator(current_v, current_w).right_wheel_speed);

    double left_speed = left_motor_controller.updateSpeed();
    int left_pwm = left_motor_controller.setPidPwm();

    double right_speed = right_motor_controller.updateSpeed();
    int right_pwm = right_motor_controller.setPidPwm();
}

