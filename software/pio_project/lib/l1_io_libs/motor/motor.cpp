#include "motor.h"

#ifndef MIN_PWM
#define MIN_PWM 0
#endif
#ifndef MAX_PWM
#define MAX_PWM 255
#endif

void Motor::setup(uint8_t dc_motor_1_pin, uint8_t dc_motor_2_pin,
                  uint8_t enable_pin, uint8_t pwm_channel) {
#if ESP32
    analog_attach_pin(enable_pin, pwm_channel);
    analog_channel_setup(pwm_channel, pwm_frequency, resolution_bits);
#endif

    pin_mode(dc_motor_1_pin, OUTPUT);
    pin_mode(dc_motor_2_pin, OUTPUT);
    digital_write(dc_motor_1_pin, LOW);
    digital_write(dc_motor_2_pin, LOW);

    this->pwm_channel = pwm_channel;
    dc_motor_1 = dc_motor_1_pin;
    dc_motor_2 = dc_motor_2_pin;
}
/**
 * @brief Sets the motor's direction of rotation
 *
 * @param _dir FORWARD or BACKWARD
 */

void Motor::set_direction(motor_rotation_dir_t motor_rotation_dir) {

    digital_write(dc_motor_1, motor_rotation_dir);
    digital_write(dc_motor_2, !motor_rotation_dir);
}

void Motor::stop() {
#if ESP32
    analog_channel_write(pwm_channel, 0);
#endif
    digital_write(dc_motor_1, LOW);
    digital_write(dc_motor_2, LOW);
}

int Motor::get_pwm() {
    return pwm_val;
}

int Motor::pwm_offset(int pwm_dif) {
    pwm_val += pwm_dif;
    if (pwm_val < MIN_PWM || pwm_val > MAX_PWM) {
        return -1;
    }
#if ESP32
    analog_channel_write(pwm_channel, 0);
#endif
    return pwm_val;
}

motor_return_t Motor::set_pwm(unsigned int _pwm_val) {
    if (_pwm_val < 0 || _pwm_val > MAX_PWM) {
        return MOTOR_ERROR;
    }
#if ESP32
    analog_channel_write(pwm_channel, 0);
#endif
    Motor::pwm_val = _pwm_val;
    return MOTOR_SUCCESS;
}

void Motor::test() {
    setup()
}