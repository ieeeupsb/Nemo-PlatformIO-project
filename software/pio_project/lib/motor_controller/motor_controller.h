#pragma once

#include "PID_v1.h"
#include "driver_controller.h"

#define PID_LOOP_INTERVAL_MS 100
#define PID_LOOP_INTERVAL_US PID_LOOP_INTERVAL_MS * 1000
// 300
// 700

class MotorController {

  private:
    PID motor_pid_;
    double pwm_output_;
    DriverController driver_controller_;
    bool is_pid_controller_enable_ = true;
    double target_speed_;
    double speed_read_;
    int encoder_count_;
    motor_rotation_dir_t motor_rotation_dir_;
    uint8_t pin_a_, pin_b_;
    unsigned long last_time_ms = 0;

  public:
    void enablePidControl() {
        is_pid_controller_enable_ = true;
        motor_pid_.SetMode(AUTOMATIC);
    }

    MotorController(int driver_enable_pin, int driver_in_a_pin, int driver_in_b_pin, int pin_a, int pin_b, double Kp, double Ki, double Kd)
        : driver_controller_(driver_enable_pin, driver_in_a_pin, driver_in_b_pin),
          motor_pid_(&speed_read_, &pwm_output_, &target_speed_, Kp, Ki, Kd, DIRECT),
          pin_a_(pin_a), pin_b_(pin_b) {

        pinMode(pin_a, INPUT);
        pinMode(pin_b, INPUT);

        driver_controller_.stopMotor();
        motor_pid_.SetMode(AUTOMATIC);
        enablePidControl();
    }

    void forceDirection(motor_rotation_dir_t dir) {
        is_pid_controller_enable_ = false;
        driver_controller_.setDirection(dir);
    }

    void SetMode(int mode) {
        motor_pid_.SetMode(mode);
    }

    void test_motor() {
        is_pid_controller_enable_ = false;

        driver_controller_.setPwm(100);
        driver_controller_.setDirection(motor_rotation_dir_t::ANTI_CLOCKWISE);
        delay(1000);
        driver_controller_.setDirection(motor_rotation_dir_t::CLOCKWISE);
        delay(1000);
        driver_controller_.stopMotor();

        is_pid_controller_enable_ = true;
    }

    void updateCount() {
        int a_state = digitalRead(pin_a_);
        int b_state = digitalRead(pin_b_);

        if (a_state == b_state) {
            encoder_count_++;
        } else {
            encoder_count_--;
        }
    }

    double updateSpeed() {
        const static unsigned long interval = 50;
        unsigned long current_time_ms = millis();
        int last_count = encoder_count_;

        if (current_time_ms - last_time_ms >= interval) {
            unsigned long delta_time_ms = current_time_ms - last_time_ms;
            encoder_count_ = 0;
            speed_read_ = 1000.00 * ((double)last_count / WHEEL_RATIO) / (double)delta_time_ms;

            if (motor_rotation_dir_t::CLOCKWISE == motor_rotation_dir_) {
                speed_read_ = -speed_read_;
            }

            last_time_ms = millis();
        }

        return speed_read_;
    }

    void forcePwm(int pwm) {
        is_pid_controller_enable_ = false;
        driver_controller_.setPwm(pwm);
    }

    void setTargetSpeed(double target_speed) {
        if (0 < target_speed) {
            driver_controller_.setDirection(motor_rotation_dir_t::CLOCKWISE);
            motor_pid_.SetControllerDirection(DIRECT);

        } else if (0 > target_speed) {
            driver_controller_.setDirection(motor_rotation_dir_t::ANTI_CLOCKWISE);
            motor_pid_.SetControllerDirection(REVERSE);

        } else {
            driver_controller_.stopMotor();
        }

        target_speed_ = target_speed;
    }

    void updateSpeedRead(double speed_read) {
        speed_read_ = speed_read;
    }

    void stopMotor() {
        driver_controller_.stopMotor();
    }

    void SetPIDConstants(double Kp, double Ki, double Kd) {
        motor_pid_.SetTunings(Kp, Ki, Kd);
    }

    bool Compute() {

        return motor_pid_.Compute();
    }

    void setPwm(unsigned int pwm) {
        driver_controller_.setPwm(pwm);
    }

    unsigned int setPidPwm() {
        static unsigned long last_time_ms = 0;
        const static unsigned long interval = 100;
        unsigned long current_time_ms = millis();
        motor_pid_.Compute();
        driver_controller_.setPwm(pwm_output_);

        if (current_time_ms - last_time_ms >= interval) {
            motor_pid_.Compute();
            driver_controller_.setPwm(pwm_output_);

            last_time_ms = millis();
        }

        return pwm_output_;
    }

    void setDirection(motor_rotation_dir_t motor_rotation_dir) {
        this->driver_controller_.setDirection(motor_rotation_dir);
        return;
    }

    int setTargetSpeedPwm() {
        updateSpeed();
        return setPidPwm();
    }

    PID *getPid() {
        return &motor_pid_;
    }

    DriverController *getDriverController() {
        return &driver_controller_;
    }

    // void test_encoders() {
    //     return
    // }
};