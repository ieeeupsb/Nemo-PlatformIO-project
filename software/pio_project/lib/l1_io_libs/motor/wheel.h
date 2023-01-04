#pragma once

#include "motor_controller.h"

enum class motor_rotation_dir_t {
    FORWARD = 1,
    BACKWARD = 0
};

class Wheel : private MotorController {
  public:
    Wheel(int m1_pin, int m2_pin, int enc_pin_a, int enc_pin_b, int pwm_motor_pin)
        : MotorController((enc_pin_a, enc_pin_b, pwm_motor_pin)) {
        // Save the pin numbers
        m1_pin_ = m1_pin;
        m2_pin_ = m2_pin;

        // Set the pins as inputs
        pinMode(m1_pin_, OUTPUT);
        pinMode(m2_pin_, OUTPUT);
    }

    void Calibrate() {

        // ...
        SetPIDConstants(1, 2, 3);
    }

    void Stop() {
        digitalWrite(m1_pin_, LOW);
        digitalWrite(m2_pin_, LOW);
        SetRpm(0);
    }

    void SetSpeed_ms(float speed_ms) {
        float target_rpm = ConvertLinearSpeedToRpm(speed_ms);
        SetRpm(target_rpm);
    }

    void SetDirection(motor_rotation_dir_t motor_rotation_dir) {
        digitalWrite(m1_pin_, (bool)motor_rotation_dir);
        digitalWrite(m2_pin_, !(bool)motor_rotation_dir);
    }

  private:
    float ConvertLinearSpeedToRpm(float linear_speed) {
        // Calculate the circumference of the wheel
        float circumference = 2 * PI * wheel_radius_;
        // Calculate the linear speed of the wheel in meters per minute
        float linear_speed_mm = linear_speed * 60;
        // Calculate the RPM of the motor
        float rpm = linear_speed_mm / circumference;
        return rpm;
    }

    int m1_pin_;
    int m2_pin_;

    static constexpr float wheel_radius_ = 360.0; // Number of pulses per revolution

    // Counters
};
