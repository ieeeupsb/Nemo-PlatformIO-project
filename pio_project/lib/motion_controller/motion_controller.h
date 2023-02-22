#pragma once

#include "PID_v1.h"
#include "driver_controller.h"
#include "pin_wiring.h"

#include "motion_equations.h"

#define WHEEL_BASE 159e-3
#define WHEEL_RATIO 3600.00

double left_speed_read_;
double right_speed_read_;

class Robot {

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

    Robot() {
        setEncoderPins(ENC_C1_PIN_L, ENC_C1_PIN_L, ENC_C1_PIN_R, ENC_C1_PIN_R);
    }
    Robot(const Robot &) = delete;
    Robot &operator=(const Robot &) = delete;

  public:
    static Robot &
    getInstance() {
        static Robot instance;
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

        // Serial.print("left_speed_read_");
        // Serial.println(left_speed_read_);
        // Serial.print("right_speed_read_");
        // Serial.println(right_speed_read_);

        wheels_speed_t wheels_current_speed;

        wheels_current_speed.left_wheel_speed = left_speed_read_;
        wheels_current_speed.right_wheel_speed = right_speed_read_;

        return wheels_current_speed;
    }

    // void test_left_encoder() {
    //     left_motor_controller.forceDirection(motor_rotation_dir_t::CLOCKWISE);
    //     left_motor_controller.forcePwm();
    //     while (true) {
    //         wheels_speed = robot.wheel_speed_calculator();
    //         if (0 != wheels_speed.left_wheel_speed) {
    //             break;
    //         }
    //         delay(100);
    //     }
    //     left_motor_controller.stopMotor();
    // }

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
};
