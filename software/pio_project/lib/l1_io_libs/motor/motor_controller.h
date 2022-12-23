#pragma once

#include "encoder.h"

class MotorController {

  private:
    Encoder encoder_;
    int pwm_motor_pin_;
    long last_count_ = 0;
    unsigned long last_time_ = 0;
    static constexpr float pulses_per_revolution_ = 360.0; // Number of pulses per revolution

  public:
    MotorController(int enc_pin_a, int enc_pin_b, int pwm_motor_pin) {
        // Initialize the encoder
        encoder_ = Encoder(enc_pin_a, enc_pin_b);

        // Set the motor control pin
        pwm_motor_pin_ = pwm_motor_pin;
    }

    void SetSpeed(int speed) {
        // Set the speed of the motor
        analogWrite(pwm_motor_pin_, speed);
    }

    float GetRpm() {
        // Calculate the current RPM of the motor
        // based on the number of encoder counts and the elapsed time
        auto count = (float)encoder_.GetCount();
        encoder_.RestartCounter();

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

    void InterruptHandler() {
        // Update the encoder count
        encoder_.Update();
    }
};