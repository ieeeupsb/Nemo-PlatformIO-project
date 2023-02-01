#pragma once

#define PICO
#include "pin_wiring.h"

#include "driver_controller.h"
#include "encoder_reader.h"
#include "mcu_api.h"

#include "motion_equations.h"

#define SPEED_TIMER_INTERVAL_MS 50

// https://github.com/br3ttb/Arduino-PID-Library

// class enum update_speed_state {
//     STATE_1 = 0,
//     STATE_2,
// };

// class enum motion_controller_state {
//     STATE_1 = 0,
//     STATE_2,
// };

// class enum serial_data_state {
//     STATE_1 = 0,
//     STATE_2,
// };

class MicroControllerUnit {
  public:
    float left_wheel_rpm;
    float right_wheel_rpm;

    static MicroControllerUnit &getInstance() {
        static MicroControllerUnit instance;
        return instance;
    }

    void updateSpeed(float enlapsed_time) {
        left_wheel_rpm = left_encoder_reader_.getCount();
        right_wheel_rpm = right_encoder_reader_.getCount();
    }

    float getLeftWheelRpm() {
        return left_wheel_rpm;
    }
    float getRightftWheelRpm() {
        return left_wheel_rpm;
    }

    // void

    void test_motors() {
        pinMode(LED_GP25, OUTPUT);
        for (int i = 0; i < 3; i++) {
            digitalWrite(LED_GP25, HIGH);
            delay(500);
            digitalWrite(LED_GP25, LOW);
            delay(500);
        }
        right_driver_controller_.setPwm(120);
        left_driver_controller_.setPwm(120);
        right_driver_controller_.setDirection(motor_rotation_dir_t::ANTI_CLOCKWISE);
        left_driver_controller_.setDirection(motor_rotation_dir_t::ANTI_CLOCKWISE);
        delay(1000);
        right_driver_controller_.setDirection(motor_rotation_dir_t::CLOCKWISE);
        left_driver_controller_.setDirection(motor_rotation_dir_t::CLOCKWISE);
        delay(1000);
        right_driver_controller_.stopMotor();
        left_driver_controller_.stopMotor();
    }

    void updateLeftCount() {
        int a_state = digitalRead(ENC_C1_PIN_L);
        int b_state = digitalRead(ENC_C2_PIN_L);

        if (a_state == b_state) {
            encoder_counter_left_++;
        } else {
            encoder_counter_left_--;
        }
    }

    void updateRightCount() {
        int a_state = digitalRead(ENC_C1_PIN_R);
        int b_state = digitalRead(ENC_C2_PIN_R);

        if (a_state == b_state) {
            encoder_counter_right++;
        } else {
            encoder_counter_right--;
        }
    }

    void speedTimerHandler() {
        float left_speed = (double)abs(encoder_counter_left_) / (double)SPEED_TIMER_INTERVAL_MS;
        float right_speed = (double)abs(encoder_counter_right_) / (double)SPEED_TIMER_INTERVAL_MS;

        rpm_last_read_left_pid_input = left_speed * 100;
        double left_linear_speed_m_per_s = left_speed * 3.1415 * 0.068 / 0.36;
        rpm_last_read_right_pid_input = right_speed * 100;
        double right_linear_speed_m_per_s = right_speed * 3.1415 * 0.068 / 0.36;

        encoder_counter_left_ = 0;
        encoder_counter_right_ = 0;

        leftWheelPID_.Compute();
        rightWheelPID_.Compute();

        left_driver_controller_.setPwm(left_pwm_output);
        right_driver_controller_.setPwm(right_pwm_output);

        current_pose = pose_estimator(current_pose_, (double)SPEED_TIMER_INTERVAL_MS / 1000.00, left_linear_speed_m_per_s, right_linear_speed_m_per_s, 159e-3);
    }

    void apiTimerHandler() {
        mcu_api_.timerHandler();
    }

    void sendInfo() {
        Serial.println("left_encoder_speed_ = " + left_encoder_speed_);
    }

    void command_state_machine() {

        const int STOP_STATE = 0;
        const int COORDINATES_COMMAND_STATE = 1;
        const int SPEED_COMMAND_STATE = 2;

        static int command_state = STOP_STATE;

        switch (command_state) {
        case STOP_STATE:
            left_driver_controller_.stopMotor();
            right_driver_controller_.stopMotor();

            if (0 != mcu_api.commandListSize() && true == last_command_done) {
                last_commmand_ = mcu_api.getNextCommand();
            }

            if (0 == last_command_.x 0 && 0 == last_command_.y) {
                command_state = SPEED_COMMAND_STATE;
            }
            if (0 == last_command_.v 0 && 0 == last_command_.w) {
                command_state = COORDINATES_COMMAND_STATE;
            }
            break;
        case COORDINATES_COMMAND_STATE:
            coordinates_state_machine();
            if (0 == last_command_.x 0 && 0 == last_command_.y && 0 == last_command_.v 0 && 0 == last_command_.w) {
                command_state = STOP_STATE;
            }
            break;
        case SPEED_COMMAND_STATE:
            speed_state_machine();
            if (0 == last_command_.x 0 && 0 == last_command_.y && 0 == last_command_.v 0 && 0 == last_command_.w) {
                command_state = STOP_STATE;
            }
            /* code */
            break;

        default:
            break;
        }
    }

  private:
    pico_command_t last_commmand_;
    last_command_done = true;

    int pin_a_l_;
    int pin_b_l_;
    int pin_a_r_;
    int pin_b_r_;

    DriverController left_driver_controller_;

    DriverController right_driver_controller_;

    McuAPI mcu_api_;
    pose_t current_pose_;

    long encoder_counter_left_;
    long encoder_counter_right_;

    double target_speed_left, rpm_last_read_left_pid_input, left_pwm_output;
    double target_speed_right, rpm_last_read_right_pid_input, right_pwm_output;

    double Kp = 1 * 0.7, Ki = 1.4, Kd = 0;

    PID leftWheelPID_(&rpm_last_read_left_pid_input, &left_pwm_output, &target_speed_left, Kp, Ki, Kd, DIRECT);
    PID rightWheelPID_(&rpm_last_read_right_pid_input, &right_pwm_output, &target_speed_right, Kp, Ki, Kd, DIRECT);

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

    MicroControllerUnit() : left_driver_controller_(DRIVER_ENABLE_PIN_L, DRIVER_IN_A_PIN_L, DRIVER_IN_B_PIN_L),
                            right_driver_controller_(DRIVER_ENABLE_PIN_R, DRIVER_IN_A_PIN_R, DRIVER_IN_B_PIN_R),
    {
        setEncoderPins(ENC_C1_PIN_L, ENC_C1_PIN_L);
        setEncoderPins(ENC_C1_PIN_R, ENC_C1_PIN_R);
    }
    MicroControllerUnit(const MicroControllerUnit &) = delete;
    MicroControllerUnit &operator=(const MicroControllerUnit &) = delete;

    void coordinates_motion_controller_state_machine() {
        pose_t target_pose;

        target_pose.x_pos = command_.x;
        target_pose.y_pos = command_.y;

        double max_speed = command_.v;

        trajectory_t trajectory = trajectory_calulator_straight_lines(current_pose_, target_pose, max_speed)
    }

    // update_speed_state sm1_state;
    // motion_controller_state sm2_state_;
    // serial_data_state sm3_state_;
}