#pragma once

#define PICO
#include "pin_wiring.h"

#include "driver_controller.h"
#include "encoder_reader.h"
#include "mcu_api.h"

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
        left_wheel_rpm = left_encoder_reader_.Update(enlapsed_time);
        right_wheel_rpm = right_encoder_reader_.Update(enlapsed_time);
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

    void update_speed_sm() {

        // switch (sm1_state) {
        // case update_speed_state::STATE_1:
        //     digitalWrite(led1, HIGH);
        //     sm1_state = update_speed_state::STATE_2;
        //     break;
        // case update_speed_state::STATE_2:
        //     digitalWrite(led1, LOW);
        //     sm1_state = update_speed_state::STATE_1;
        //     break;
        // }
    }

    void robot_motion_controller_sm() {
        // switch (sm2_state_) {
        // case motion_controller_state::STATE_1:
        //     digitalWrite(led2, HIGH);
        //     sm2_state_ = motion_controller_state::STATE_2;
        //     break;
        // case motion_controller_state::STATE_2:
        //     digitalWrite(led2, LOW);
        //     sm2_state_ = motion_controller_state::STATE_1;
        //     break;
        // }
    }

    void serial_data_sm() {
        // switch (sm3_state_) {
        // case serial_data_state::STATE_1:
        //     digitalWrite(led3, HIGH);
        //     sm3_state_ = serial_data_state::STATE_2;
        //     break;
        // case serial_data_state::STATE_2:
        //     digitalWrite(led3, LOW);
        //     sm3_state_ = serial_data_state::STATE_1;
        //     break;
        // }
    }

  private:
    MicroControllerUnit() : left_driver_controller_(DRIVER_ENABLE_PIN_L, DRIVER_IN_A_PIN_L, DRIVER_IN_B_PIN_L),
                            right_driver_controller_(DRIVER_ENABLE_PIN_R, DRIVER_IN_A_PIN_R, DRIVER_IN_B_PIN_R),
                            left_encoder_reader_(ENC_C1_PIN_L, ENC_C1_PIN_L),
                            right_encoder_reader_(ENC_C1_PIN_R, ENC_C1_PIN_R) {}
    MicroControllerUnit(const MicroControllerUnit &) = delete;
    MicroControllerUnit &operator=(const MicroControllerUnit &) = delete;

    DriverController left_driver_controller_;
    EncoderReader left_encoder_reader_;

    DriverController right_driver_controller_;
    EncoderReader right_encoder_reader_;

    McuAPI mcu_api_;

    // update_speed_state sm1_state;
    // motion_controller_state sm2_state_;
    // serial_data_state sm3_state_;
};