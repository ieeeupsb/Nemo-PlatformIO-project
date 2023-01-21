#pragma once

#include "driver_controller.h"
#include "encoder_reader.h"

struct motor_controller_pins_t {
    int driver_in_a;
    int driver_in_b;
    int driver_enable_pin;
    int enc_pin_a;
    int enc_pin_b;
};

#define RPM_TOLERANCE 5

class MotorController {

  private:
    EncoderReader encoder_reader_;
    DriverController driver_controller_;

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

  public:
    MotorController(int enc_pin_a, int enc_pin_b, int driver_enable_pin, int driver_in_a, int driver_in_b)
        // Initialize the encoder
        : encoder_reader_(enc_pin_a, enc_pin_b),
          driver_controller_(driver_enable_pin, driver_in_a, driver_in_b) {}

    void stopMotor() {
        driver_controller_.stopMotor();
    }

    float getRpm() {
        // Calculate the current RPM of the motor
        // based on the number of encoder counts and the elapsed time
        // auto count = (float)encoder_reader_.GetSpeedCount();
        // encoder_reader_.RestartSpeedCounter();

        // unsigned long current_time = millis();
        // float elapsed_time_ms = (current_time - last_time_); // elapsed time in milliseconds
        // last_time_ = current_time;

        //...not tested
        // float n_rotations = (count / pulses_per_revolution_); //
        // float time_s = elapsed_time_ms / 1000;
        // float rpm = n_rotations / time_s;
        //...end of not tested

        // return count;
        return 0;
    }

    void setRpm(int target_rpm, int acceleration) {
        if (0 == target_rpm) {
            stopMotor();
            return;
        }

        target_rpm_ = target_rpm;
        acceleration_ = acceleration;
    }

    void setRpm(int target_rpm) {

        setRpm(target_rpm, 0);
    }
};

// // MotorController(motor_controller_pins_t motor_controller_pins)
// //     // Initialize the encoder
// //     : encoder_reader_(motor_controller_pins.enc_pin_a, motor_controller_pins.enc_pin_b),
// //       MotorDriverController(motor_controller_pins.driver_enable_pin, motor_controller_pins.driver_in_a, motor_controller_pins.driver_in_b) {

// //     // Set the motor control pin
// // }

// void rpmController() {
//     // Calculate the current RPM of the motor
//     float current_rpm = getRpm();

//     // Calculate the error between the target RPM and the current RPM
//     float error = target_rpm_ - current_rpm;

//     if (abs(error) < RPM_TOLERANCE) {
//         acceleration_ = 0;
//     }

//     // Update the error sum for the integral term
//     error_sum_ += error;

//     // Calculate the derivative term
//     float derivative = error - last_error_;

//     // Calculate the output of the PID controller
//     int output = kp_ * error + ki_ * error_sum_ + kd_ * derivative + acceleration_;

//     driver_controller_.setPwm(output);

//     // Update the last error for the next iteration
//     last_error_ = error;
// }

// void encoderReaderInterruptHandler() {
//     // Update the encoder count
//     encoder_reader_.Update();
//     // Serial.println("Encoder Interrupt");
// }

// void setPIDConstants(float kp, float ki, float kd) {
//     kp_ = kp;
//     ki_ = ki;
//     kd_ = kd;
// }

// void calibrate() {

//     // ...
//     setPIDConstants(1, 2, 3);
// }

// void stop() {
//     digitalWrite(m1_pin_, LOW);
//     digitalWrite(m2_pin_, LOW);
//     setRpm(0);

//     driver_controller_.stop();
// }

// // void setSpeed_ms(float speed_ms) {
// //     float target_rpm = ConvertLinearSpeedToRpm(speed_ms);
// //     setRpm(target_rpm);
// // }
