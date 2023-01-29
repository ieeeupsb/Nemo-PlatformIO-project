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

        pinMode(LED_GP25, OUTPUT);

        for (int i = 0; i < 3; i++) {
            digitalWrite(LED_GP25, HIGH);
            delay(200);
            digitalWrite(LED_GP25, LOW);
            delay(200);
        }

        pinMode(enable, OUTPUT);
        pinMode(in_a, OUTPUT);
        pinMode(in_b, OUTPUT);
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
