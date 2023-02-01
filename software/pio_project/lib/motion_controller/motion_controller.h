#pragma once

#include "PID_v1.h"
#include "driver_controller.h"
#include "pin_wiring.h"

#include "motion_equations.h"

#define WHEEL_BASE 0.19

double target_speed_left_, left_speed_read_, left_pwm_output_;
double target_speed_right_, right_speed_read_, right_pwm_output_;

double Kp = 1 * 0.7, Ki = 1.4, Kd = 0;

PID leftWheelPID_(&left_speed_read_, &left_pwm_output_, &target_speed_left_, Kp, Ki, Kd, DIRECT);
PID rightWheelPID_(&right_speed_read_, &right_pwm_output_, &target_speed_right_, Kp, Ki, Kd, DIRECT);

class MotionController {

  private:
    bool last_command_done_ = true;

    int pin_a_l_;
    int pin_b_l_;
    int pin_a_r_;
    int pin_b_r_;

    int encoder_counter_left_;
    int encoder_counter_right_;

    DriverController left_driver_controller_;
    DriverController right_driver_controller_;

    pose_t current_pose_;

    void coordinates_state_machine(double x, double y) {
        const int GOING_TO_COORDINATES_STATE = 0;
        const int CHECK_POSITION_STATE = 1;

        static int current_state = GOING_TO_COORDINATES_STATE;

        switch (current_state) {
        case GOING_TO_COORDINATES_STATE:
            last_command_done_ = false;
            Serial.println("going to coordinate...");

            current_state = CHECK_POSITION_STATE;
            break;
        case CHECK_POSITION_STATE:
            Serial.println("reach the coordinate");
            last_command_done_ = true;

        default:
            break;
        }
    }

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
    }
    MotionController(const MotionController &) = delete;
    MotionController &operator=(const MotionController &) = delete;

    void go_to_coordinates(double x, double y, double v) {

        // trajectory_t trajectory = trajectory_calulator_straight_lines(current_pose_, target_pose, max_speed);

        Serial.println("Calculating trajectory...");
        set_v_w_speeds(0, 0);
    }

    void set_v_w_speeds(double v, double w) {

        if (v < 0) {
            left_driver_controller_.setDirection(motor_rotation_dir_t::CLOCKWISE);
            right_driver_controller_.setDirection(motor_rotation_dir_t::ANTI_CLOCKWISE);
        } else if (v > 0) {
            left_driver_controller_.setDirection(motor_rotation_dir_t::ANTI_CLOCKWISE);
            right_driver_controller_.setDirection(motor_rotation_dir_t::CLOCKWISE);
        } else if (w < 0) {
            left_driver_controller_.setDirection(motor_rotation_dir_t::CLOCKWISE);
            right_driver_controller_.setDirection(motor_rotation_dir_t::CLOCKWISE);
        } else if (w > 0) {
            left_driver_controller_.setDirection(motor_rotation_dir_t::ANTI_CLOCKWISE);
            right_driver_controller_.setDirection(motor_rotation_dir_t::ANTI_CLOCKWISE);
        } else {
            left_driver_controller_.stopMotor();
            right_driver_controller_.stopMotor();
        }

        target_speed_left_ = v - (w * WHEEL_BASE) / 2;
        target_speed_right_ = v + (w * WHEEL_BASE) / 2;
    }

  public:
    static MotionController &
    getInstance() {
        static MotionController instance;
        return instance;
    }

    void speedTimerHandler() {
        left_speed_read_ = (double)abs(encoder_counter_left_) / (double)SPEED_TIMER_INTERVAL_MS;
        left_speed_read_ = (double)abs(encoder_counter_right_) / (double)SPEED_TIMER_INTERVAL_MS;

        Serial.print("left_speed:");
        Serial.println(left_speed_read_);
        Serial.print("right_speed:");
        Serial.println(right_speed_read_);

        double left_linear_speed = left_speed_read_ * 3.1415 * 0.068 / 0.36;
        double right_linear_speed = left_speed_read_ * 3.1415 * 0.068 / 0.36;

        encoder_counter_left_ = 0;
        encoder_counter_right_ = 0;

        leftWheelPID_.Compute();
        rightWheelPID_.Compute();

        left_driver_controller_.setPwm(left_pwm_output_);
        right_driver_controller_.setPwm(right_pwm_output_);

        current_pose_ = pose_estimator(current_pose_, (double)SPEED_TIMER_INTERVAL_MS / 1000.00, left_linear_speed, right_linear_speed, 159e-3);
    }

    bool command_state_machine(double x, double y, double v, double w) {

        const int STOP_STATE = 0;
        const int COORDINATES_COMMAND_STATE = 1;
        const int SPEED_COMMAND_STATE = 2;

        static int command_state = STOP_STATE;

        switch (command_state) {
        case STOP_STATE:
            left_driver_controller_.stopMotor();
            right_driver_controller_.stopMotor();

            if (0 == v && 0 == w) {
                command_state = STOP_STATE;
                break;
            }

            if (0 == x && 0 == y && (0 != v || 0 != w)) {
                Serial.println("Going to remote controlled state...");

                command_state = SPEED_COMMAND_STATE;
                break;
            }
            if (0 == w && 0 != v && (0 != x || 0 != y)) {
                Serial.println("Going to recieve coordinates state...");

                command_state = COORDINATES_COMMAND_STATE;
                break;
            }
        case COORDINATES_COMMAND_STATE:
            coordinates_state_machine(x, y);
            if (0 == v && 0 == w) {
                Serial.println("Going to stop state...");
                command_state = STOP_STATE;
                break;
            }
        case SPEED_COMMAND_STATE:
            set_v_w_speeds(v, w);
            last_command_done_ = true;
            if (0 == v && 0 == w) {
                Serial.println("Going to stop state...");
                command_state = STOP_STATE;
                break;
            }

        default:
            command_state = STOP_STATE;
            break;
        }

        return last_command_done_;
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

//     void test_motors() {
//         pinMode(LED_GP25, OUTPUT);
//         for (int i = 0; i < 3; i++) {
//             digitalWrite(LED_GP25, HIGH);
//             delay(500);
//             digitalWrite(LED_GP25, LOW);
//             delay(500);
//         }
//         right_driver_controller_.setPwm(120);
//         left_driver_controller_.setPwm(120);
//         right_driver_controller_.setDirection(motor_rotation_dir_t::ANTI_CLOCKWISE);
//         left_driver_controller_.setDirection(motor_rotation_dir_t::ANTI_CLOCKWISE);
//         delay(1000);
//         right_driver_controller_.setDirection(motor_rotation_dir_t::CLOCKWISE);
//         left_driver_controller_.setDirection(motor_rotation_dir_t::CLOCKWISE);
//         delay(1000);
//         right_driver_controller_.stopMotor();
//         left_driver_controller_.stopMotor();
//     }
