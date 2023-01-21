#pragma once

#include "Arduino.h"

enum class motor_rotation_dir_t {
    CLOCKWISE = 0,
    ANTI_CLOCKWISE
};

class DriverController {
  private:
    int enable_;
    int in_a_;
    int in_b_;

  public:
    void setMotorDriverPins(int enable, int in_a, int in_b) {
        enable_ = enable;
        in_a_ = in_a;
        in_b_ = in_b;
    }

    DriverController(int enable, int in_a, int in_b) {
        setMotorDriverPins(enable, in_a, in_b);
    }

    void setDirection(motor_rotation_dir_t motor_rotation_dir) {
        digitalWrite(in_a_, (bool)motor_rotation_dir);
        digitalWrite(in_b_, !(bool)motor_rotation_dir);
    }

    void setPwm(int duty_cycle) {

        duty_cycle = constrain(duty_cycle, 0, 255);
        analogWrite(enable_, duty_cycle);
    }

    void stopMotor() {
        digitalWrite(in_a_, LOW);
        digitalWrite(in_b_, LOW);
        setPwm(0);
    }
};

void driver_test() {
    DriverController driver_controller(DRIVER_ENABLE_PIN_L, DRIVER_IN_A_PIN_L, DRIVER_IN_B_PIN_L);

    driver_controller.setPwm(120);
    driver_controller.setDirection(motor_rotation_dir_t::ANTI_CLOCKWISE);
    delay(1000);
    driver_controller.setDirection(motor_rotation_dir_t::CLOCKWISE);
    delay(1000);
    driver_controller.stopMotor();
}
