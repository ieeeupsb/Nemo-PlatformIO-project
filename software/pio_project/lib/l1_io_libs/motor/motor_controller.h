#pragma once

#include "encoder.h"

#define RPM_TOLERANCE 5

class MotorController {

  private:
    Encoder encoder_;
    int pwm_motor_pin_;
    long last_count_ = 0;
    unsigned long last_time_ = 0;
    static constexpr float pulses_per_revolution_ = 360.0; // Number of pulses per revolution
    int target_rpm_;
    float acceleration_;

    // PID controller constants
    float kp_ = 0.0;
    float ki_ = 0.0;
    float kd_ = 0.0;

    // PID controller state variables
    float error_sum_ = 0.0;
    float last_error_ = 0.0;

  public:
    MotorController(int enc_pin_a, int enc_pin_b, int pwm_motor_pin)
        // Initialize the encoder
        : encoder_(enc_pin_a, enc_pin_b) {

        // Set the motor control pin
        pwm_motor_pin_ = pwm_motor_pin;
    }

    void SetPIDConstants(float kp, float ki, float kd) {
        kp_ = kp;
        ki_ = ki;
        kd_ = kd;
    }

    void SetRpm(int target_rpm, int acceleration) {
        if (0 == target_rpm) {
            analogWrite(pwm_motor_pin_, 0);
            return;
        }

        target_rpm_ = target_rpm;
        acceleration_ = acceleration;
    }

    void SetRpm(int target_rpm) {

        SetRpm(target_rpm, 0);
    }

    float GetRpm() {
        // Calculate the current RPM of the motor
        // based on the number of encoder counts and the elapsed time
        auto count = (float)encoder_.GetSpeedCount();
        encoder_.RestartSpeedCounter();

        unsigned long current_time = millis();
        float elapsed_time_ms = (current_time - last_time_); // elapsed time in milliseconds
        last_time_ = current_time;

        //...not tested
        float n_rotations = (count / pulses_per_revolution_); //
        float time_s = elapsed_time_ms / 1000;
        float rpm = n_rotations / time_s;
        //...end of not tested

        return rpm;
    }

    void RpmController() {
        // Calculate the current RPM of the motor
        float current_rpm = GetRpm();

        // Calculate the error between the target RPM and the current RPM
        float error = target_rpm_ - current_rpm;

        if (abs(error) < RPM_TOLERANCE) {
            acceleration_ = 0;
        }

        // Update the error sum for the integral term
        error_sum_ += error;

        // Calculate the derivative term
        float derivative = error - last_error_;

        // Calculate the output of the PID controller
        float output = kp_ * error + ki_ * error_sum_ + kd_ * derivative + acceleration_;

        // Constrain the output to the range of the motor PWM signal
        output = constrain(output, 0, 255);

        // Set the speed of the motor
        analogWrite(pwm_motor_pin_, output);

        // Update the last error for the next iteration
        last_error_ = error;
    }

    void InterruptHandler() {
        // Update the encoder count
        encoder_.Update();
    }
};