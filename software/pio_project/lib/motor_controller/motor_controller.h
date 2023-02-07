#pragma once

#include "PID_v1.h"
#include "driver_controller.h"

#define PID_LOOP_INTERVAL_MS 100
#define PID_LOOP_INTERVAL_US PID_LOOP_INTERVAL_MS * 1000

class MotorController {

  private:
    PID motor_pid_;
    double pwm_output_;
    DriverController driver_controller_;
    bool is_pid_controller_enable_ = true;
    double target_speed_;
    double speed_read_;

  public:
    void enablePidControl() {
        is_pid_controller_enable_ = true;
    }

    MotorController(int driver_enable_pin, int driver_in_a_pin, int driver_in_b_pin, double Kp, double Ki, double Kd)
        : driver_controller_(driver_enable_pin, driver_in_a_pin, driver_in_b_pin),
          motor_pid_(&speed_read_, &pwm_output_, &target_speed_, Kp, Ki, Kd, DIRECT) {

        driver_controller_.stopMotor();
        motor_pid_.SetMode(AUTOMATIC);
        enablePidControl();
        // motor_pid_.SetSampleTime(PID_LOOP_INTERVAL_MS);
        // motor_pid_.SetOutputLimits(40, 255);
    }

    void forceDirection(motor_rotation_dir_t dir) {
        is_pid_controller_enable_ = false;
        driver_controller_.setDirection(dir);
    }

    void test_motor() {
        is_pid_controller_enable_ = false;

        driver_controller_.setPwm(100);
        driver_controller_.setDirection(motor_rotation_dir_t::ANTI_CLOCKWISE);
        delay(1000);
        driver_controller_.setDirection(motor_rotation_dir_t::CLOCKWISE);
        delay(1000);
        driver_controller_.stopMotor();

        is_pid_controller_enable_ = true;
    }

    void forcePwm(int pwm) {
        is_pid_controller_enable_ = false;
        driver_controller_.setPwm(pwm);
    }

    void setTargetSpeed(double target_speed) {
        if (0 < target_speed) {
            driver_controller_.setDirection(motor_rotation_dir_t::CLOCKWISE);
        } else if (0 > target_speed) {
            driver_controller_.setDirection(motor_rotation_dir_t::ANTI_CLOCKWISE);
        } else {
            driver_controller_.stopMotor();
        }

        target_speed_ = abs(target_speed);
    }

    void updateSpeedRead(double speed_read) {
        speed_read_ = speed_read;
    }

    void stopMotor() {
        driver_controller_.stopMotor();
    }

    void SetPIDConstants(double Kp, double Ki, double Kd) {
        motor_pid_.SetTunings(Kp, Ki, Kd);
    }

    bool Compute() {

        return motor_pid_.Compute();
    }

    void setPwm(unsigned int pwm) {
        driver_controller_.setPwm(pwm);
    }

    void setPidPwm() {
        driver_controller_.setPwm(pwm_output_);
        Serial.println(pwm_output_);
    }

    PID *getPid() {
        return &motor_pid_;
    }

    DriverController *getDriverController() {
        return &driver_controller_;
    }

    // void test_encoders() {
    //     return
    // }

    // void motor_controller(double left_speed_target, double right_speed_target) {

    //     if (!left_speed_target && !right_speed_target) {
    //         left_driver_controller_.stopMotor();
    //         right_driver_controller_.stopMotor();
    //         return;
    //     }

    //     if (left_speed_target < 0) {
    //         left_driver_controller_.setDirection(motor_rotation_dir_t::CLOCKWISE);
    //     } else if (left_speed_target > 0) {
    //         left_driver_controller_.setDirection(motor_rotation_dir_t::ANTI_CLOCKWISE);
    //     } else {
    //         left_driver_controller_.stopMotor();
    //     }

    //     if (right_speed_target < 0) {
    //         right_driver_controller_.setDirection(motor_rotation_dir_t::ANTI_CLOCKWISE);
    //     } else if (right_speed_target > 0) {
    //         right_driver_controller_.setDirection(motor_rotation_dir_t::CLOCKWISE);
    //     } else {
    //         right_driver_controller_.stopMotor();
    //     }

    //     // const double KP_20_40 = 1;
    //     // const double KI_20_40 = 0;

    //     // if (0.20 < abs(left_speed_target) && abs(left_speed_target) <= 0.40) { // low speed

    //     //     leftWheelPID_.SetTunings(KP_20_40, 0, 0);
    //     // } else if (0.40 < abs(left_speed_target) && abs(left_speed_target) <= 0.60) { // mid speed

    //     //     leftWheelPID_.SetTunings(50 * 0.6, 10, 0);
    //     // }

    //     // if (0.20 < abs(right_speed_target) && abs(right_speed_target) <= 0.40) { // low speed

    //     //     rightWheelPID_.SetTunings(KP_20_40, 0, 0);
    //     // } else if (0.40 < abs(right_speed_target) && abs(right_speed_target) <= 0.60) { // mid speed

    //     //     rightWheelPID_.SetTunings(50 * 0.6, 10, 0);
    //     // }

    //     left_speed_pid_output_ = left_speed_target;
    //     right_speed_pid_output_ = right_speed_target;

    //     // if (left_speed_read_ == 0) {
    //     //     left_pwm_output_ = 90;
    //     // } else {
    //     leftWheelPID_.Compute();
    //     // Serial.print("left pwm:");
    //     // Serial.println(left_pwm_output_);
    //     // }

    //     // if (right_speed_read_ == 0) {
    //     //     right_pwm_output_ = 90;
    //     // }
    //     // else {
    //     rightWheelPID_.Compute();
    //     // Serial.print("right pwm:");
    //     // Serial.println(right_pwm_output_);
    //     // }

    //     left_driver_controller_.setPwm(left_pwm_output_);
    //     right_driver_controller_.setPwm(right_pwm_output_);

    //     // // // left_driver_controller_.setPwm(55);
    //     // // // right_driver_controller_.setPwm(55);

    //     // // // Serial.print("kp:");
    //     // // // Serial.println(leftWheelPID_.GetKp());
    // }
};