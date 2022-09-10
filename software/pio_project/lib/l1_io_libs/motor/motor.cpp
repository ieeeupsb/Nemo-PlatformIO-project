#include "motor.h"

void Motor::setup(uint8_t dc_motor_1_pin, uint8_t dc_motor_2_pin,
                  uint8_t enable_pin, uint8_t pwm_channel) {
#if ESP32
    // For using the analog pins with the ESP32 it is necessary to configure a PWM channel.
    analog_attach_pin(enable_pin, pwm_channel);
    analog_channel_setup(pwm_channel, pwm_frequency, resolution_bits);
    this->pwm_channel = pwm_channel;
    // For using the analog pins with the ESP32 it is necessary to configure a PWM channel.
#endif

    pin_mode(dc_motor_1_pin, OUTPUT);
    pin_mode(dc_motor_2_pin, OUTPUT);
    digital_write(dc_motor_1_pin, LOW);
    digital_write(dc_motor_2_pin, LOW);

    dc_motor_1 = dc_motor_1_pin;
    dc_motor_2 = dc_motor_2_pin;
}

void Motor::stop() {
#if ESP32
    analog_channel_write(pwm_channel, 0);
#endif
    digital_write(dc_motor_1, LOW);
    digital_write(dc_motor_2, LOW);
}

void Motor::set_direction(motor_rotation_dir_t motor_rotation_dir) {

    digital_write(dc_motor_1, motor_rotation_dir);
    digital_write(dc_motor_2, !motor_rotation_dir);
}

motor_return_t Motor::set_pwm(pwm_t pwm_val) {
    if (pwm_val < 0 || pwm_val > MAX_PWM) {
        return MOTOR_ERROR;
    }
#if ESP32
    analog_channel_write(pwm_channel, 0);

    // else case not tested
    // analog_write(enable_pin, current_pwm);
#endif
    Motor::current_pwm = pwm_val;
    return MOTOR_SUCCESS;
}

motor_return_t Motor::pwm_offset(pwm_t offset_val) {

    pwm_t new_pwm = current_pwm + offset_val;

    return set_pwm(new_pwm);
}

pwm_t Motor::get_pwm() {
    return current_pwm;
}