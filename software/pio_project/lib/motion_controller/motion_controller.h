#pragma once

#include "PID_v1.h"
#include "driver_controller.h"
#include "pin_wiring.h"

#include "motion_equations.h"

#define WHEEL_BASE 159e-3
#define WHEEL_RATIO 3600.00

double left_speed_pid_output_, left_speed_read_;
double left_pwm_output_ = 0;
double right_speed_pid_output_, right_speed_read_;
double right_pwm_output_ = 0;

// double Kp = 50 * 0.6;
// double Ki = 10;
// double Kd = 0;
double Kp = 0;
double Ki = 0;
double Kd = 0;
// * 0.7, Ki = 0, Kd = 0;5
// double Kp = 10 * 1, Ki = 10 * 1.4, Kd = 0;

PID leftWheelPID_(&left_speed_read_, &left_pwm_output_, &left_speed_pid_output_, Kp, Ki, Kd, DIRECT);
PID rightWheelPID_(&right_speed_read_, &right_pwm_output_, &right_speed_pid_output_, Kp, Ki, Kd, DIRECT);

class MotionController {

  private:
    bool last_command_done_ = true;
    bool is_pid_controller_enable_ = true;

    unsigned int speed_read_last_time_ms_;

    int pin_a_l_;
    int pin_b_l_;
    int pin_a_r_;
    int pin_b_r_;

    int encoder_counter_left_;
    int encoder_counter_right_;

    DriverController left_driver_controller_;
    DriverController right_driver_controller_;

    pose_t current_pose_;

    void setEncoderPins(int pin_a_l, int pin_b_l, int pin_a_r, int pin_b_r) {

        // Set the pins as inputs
        pinMode(pin_a_l, INPUT);
        pinMode(pin_b_l, INPUT);
        pinMode(pin_a_r, INPUT);
        pinMode(pin_b_r, INPUT);

        pin_a_l_ = pin_a_l;
        pin_b_l_ = pin_b_l;
        pin_a_r_ = pin_a_r;
        pin_b_r_ = pin_b_r;
    }

    MotionController() : left_driver_controller_(DRIVER_ENABLE_PIN_L, DRIVER_IN_A_PIN_L, DRIVER_IN_B_PIN_L),
                         right_driver_controller_(DRIVER_ENABLE_PIN_R, DRIVER_IN_A_PIN_R, DRIVER_IN_B_PIN_R) {
        setEncoderPins(ENC_C1_PIN_L, ENC_C1_PIN_L, ENC_C1_PIN_R, ENC_C1_PIN_R);
        leftWheelPID_.SetMode(AUTOMATIC);
        rightWheelPID_.SetMode(AUTOMATIC);
        left_driver_controller_.stopMotor();
        right_driver_controller_.stopMotor();
    }
    MotionController(const MotionController &) = delete;
    MotionController &operator=(const MotionController &) = delete;

  public:
    static MotionController &
    getInstance() {
        static MotionController instance;
        return instance;
    }

    wheels_speed_t wheel_speed_calculator() {
        static long last_time_mu = 0;
        static long current_time_mu;

        last_time_mu = current_time_mu;
        current_time_mu = micros();

        double delta_time_mu = (double)(current_time_mu - last_time_mu);

        left_speed_read_ = 1000000.00 * ((double)abs(encoder_counter_left_) / WHEEL_RATIO) / delta_time_mu;
        right_speed_read_ = 1000000.00 * ((double)abs(encoder_counter_right_) / WHEEL_RATIO) / delta_time_mu;

        // Serial.print(" encoder_counter_left_:");
        // Serial.println(encoder_counter_right_);

        encoder_counter_left_ = 0;
        encoder_counter_right_ = 0;

        Serial.print("left_speed_read_");
        Serial.println(left_speed_read_);
        Serial.print("right_speed_read_");
        Serial.println(right_speed_read_);

        wheels_speed_t wheels_current_speed;

        wheels_current_speed.left_wheel_speed = left_speed_read_;
        wheels_current_speed.right_wheel_speed = right_speed_read_;

        return wheels_current_speed;
    }

    pose_t estimate_postion() {
        current_pose_ = pose_estimator(current_pose_, (double)speed_read_last_time_ms_ / 1000.00, left_speed_read_, right_speed_read_, WHEEL_BASE);

        return current_pose_;
    }

    trajectory_t motion_controller(int x, int y) {

        pose_t target_coordinate;
        target_coordinate.x_pos = x;
        target_coordinate.y_pos = y;

        return trajectory_calulator_straight_lines(current_pose_, target_coordinate, 1.0);
    }

    wheels_speed_t velocities_generator(double v, double w) {

        wheels_speed_t generate_speeds;

        generate_speeds.left_wheel_speed = v - (w * WHEEL_BASE) / 2;
        generate_speeds.right_wheel_speed = v + (w * WHEEL_BASE) / 2;

        return generate_speeds;
    }

    void motor_controller(double left_speed_target, double right_speed_target) {

        if (!left_speed_target && !right_speed_target) {
            left_driver_controller_.stopMotor();
            right_driver_controller_.stopMotor();
            return;
        }

        const double KP_20_40 = 1;
        const double KI_20_40 = 0;

        if (0.20 < abs(left_speed_target) && abs(left_speed_target) <= 0.40) { // low speed

            leftWheelPID_.SetTunings(KP_20_40, 0, 0);
        } else if (0.40 < abs(left_speed_target) && abs(left_speed_target) <= 0.60) { // mid speed

            leftWheelPID_.SetTunings(50 * 0.6, 10, 0);
        }

        if (0.20 < abs(right_speed_target) && abs(right_speed_target) <= 0.40) { // low speed

            rightWheelPID_.SetTunings(KP_20_40, 0, 0);
        } else if (0.40 < abs(right_speed_target) && abs(right_speed_target) <= 0.60) { // mid speed

            rightWheelPID_.SetTunings(50 * 0.6, 10, 0);
        }

        left_speed_pid_output_ = left_speed_target;
        right_speed_pid_output_ = right_speed_target;

        leftWheelPID_.Compute();
        rightWheelPID_.Compute();

        if (left_speed_target < 0) {
            left_driver_controller_.setDirection(motor_rotation_dir_t::CLOCKWISE);
        } else if (left_speed_target > 0) {
            left_driver_controller_.setDirection(motor_rotation_dir_t::ANTI_CLOCKWISE);
        } else {
            left_driver_controller_.stopMotor();
        }

        if (right_speed_target < 0) {
            right_driver_controller_.setDirection(motor_rotation_dir_t::ANTI_CLOCKWISE);
        } else if (right_speed_target > 0) {
            right_driver_controller_.setDirection(motor_rotation_dir_t::CLOCKWISE);
        } else {
            right_driver_controller_.stopMotor();
        }

        left_driver_controller_.setPwm(left_pwm_output_);
        right_driver_controller_.setPwm(right_pwm_output_);

        if (left_speed_read_ == 0) {
            leftWheelPID_.SetOutputLimits(90, 95);
        }

        if (right_speed_read_ == 0) {
            Serial.println("turabao");

            rightWheelPID_.SetOutputLimits(90, 95);
        }
        leftWheelPID_.SetOutputLimits(0, 95);
        rightWheelPID_.SetOutputLimits(0, 95);

        // // // left_driver_controller_.setPwm(55);
        // // // right_driver_controller_.setPwm(55);

        // // // Serial.print("kp:");
        // // // Serial.println(leftWheelPID_.GetKp());
        Serial.print("left pwm:");
        Serial.println(left_pwm_output_);
    }

    void updateRightCount() {
        int a_state = digitalRead(pin_a_r_);
        int b_state = digitalRead(pin_b_r_);

        if (a_state == b_state) {
            encoder_counter_right_++;
        } else {
            encoder_counter_right_--;
        }
    }

    void updateLeftCount() {
        int a_state = digitalRead(pin_a_l_);
        int b_state = digitalRead(pin_b_l_);

        if (a_state == b_state) {
            encoder_counter_left_++;
        } else {
            encoder_counter_left_--;
        }
    }

    void test_motors() {
        is_pid_controller_enable_ = false;
        pinMode(LED_GP25, OUTPUT);
        for (int i = 0; i < 3; i++) {
            digitalWrite(LED_GP25, HIGH);
            delay(500);
            digitalWrite(LED_GP25, LOW);
            delay(500);
        }
        right_driver_controller_.setPwm(80);
        left_driver_controller_.setPwm(80);
        right_driver_controller_.setDirection(motor_rotation_dir_t::ANTI_CLOCKWISE);
        left_driver_controller_.setDirection(motor_rotation_dir_t::ANTI_CLOCKWISE);
        delay(1000);
        right_driver_controller_.setDirection(motor_rotation_dir_t::CLOCKWISE);
        left_driver_controller_.setDirection(motor_rotation_dir_t::CLOCKWISE);
        delay(1000);
        right_driver_controller_.stopMotor();
        left_driver_controller_.stopMotor();
        is_pid_controller_enable_ = true;
    }

    void test_encoders() {
        is_pid_controller_enable_ = false;
        pinMode(LED_GP25, OUTPUT);
        for (int i = 0; i < 3; i++) {
            digitalWrite(LED_GP25, HIGH);
            delay(500);
            digitalWrite(LED_GP25, LOW);
            delay(500);
        }
        right_driver_controller_.setPwm(80);
        left_driver_controller_.setPwm(80);
        right_driver_controller_.setDirection(motor_rotation_dir_t::ANTI_CLOCKWISE);
        left_driver_controller_.setDirection(motor_rotation_dir_t::ANTI_CLOCKWISE);
        while (encoder_counter_left_ && encoder_counter_right_) {
        }
        right_driver_controller_.stopMotor();
        left_driver_controller_.stopMotor();
        is_pid_controller_enable_ = true;
    }
};

//     McuAPI mcu_api_;
//     pose_t current_pose_;

//     long encoder_counter_left_;
//     long encoder_counter_right_;

//   public:
//     float left_wheel_rpm;
//     float right_wheel_rpm;

//     float getLeftWheelRpm() {
//         return left_wheel_rpm;
//     }
//     float getRightftWheelRpm() {
//         return left_wheel_rpm;
//     }

//     // void
