#include "motor.h"

#ifndef MIN_PWM
#define MIN_PWM 0
#endif
#ifndef MAX_PWM
#define MAX_PWM 255
#endif

void Motor::setup(uint8_t dc_motor_1_pin, uint8_t dc_motor_2_pin,
                  uint8_t enable_pin, uint8_t channel, int enc1_pin,
                  int enc2_pin) {
    ledcAttachPin(enable_pin, channel);
    ledcSetup(channel, pwm_frequency, resolution_bits);
    pinMode(dc_motor_1_pin, OUTPUT);
    pinMode(dc_motor_2_pin, OUTPUT);
    digitalWrite(dc_motor_1_pin, LOW);
    digitalWrite(dc_motor_2_pin, LOW);

    pwm_channel = channel;
    dc_motor_1 = dc_motor_1_pin;
    dc_motor_2 = dc_motor_2_pin;

    encoder.attachHalfQuad(enc1_pin, enc2_pin);
}
/**
 * @brief Sets the motor's direction of rotation
 *
 * @param _dir FORWARD or BACKWARD
 */

int Motor::set_direction(uint8_t _dir) {
    if (_dir != FORWARD && _dir != BACKWARDS) {
        return MOTOR_ERROR;
    }

    digitalWrite(dc_motor_1, _dir);
    digitalWrite(dc_motor_2, !_dir);
    dir = _dir;

    return MOTOR_SUCCESS;
}

void Motor::stop() {
    ledcWrite(pwm_channel, 0);
    digitalWrite(dc_motor_1, LOW);
    digitalWrite(dc_motor_2, LOW);
}

// TODO : test this function with the robot
float Motor::get_speed() {
    float current_tick_number = (float)encoder.getCount();
    float current_time = (float)millis();
    float distance =
        (current_tick_number - previous_tick_number) * WALK_CONST; // in mm
    float time = (current_time - previous_time);                   // in ms

    if (!distance || !time) // if the distance or the time diference is zero
                            // acceleration is zero
        return Motor::current_speed;

    Motor::current_speed = distance / time;

    // Refresh previous_vars in the end of the function
    previous_tick_number = encoder.getCount();
    previous_time = millis();

    return Motor::current_speed;
}

int Motor::get_pwm() {
    return pwmVal;
}

int Motor::pwm_offset(int pwm_dif) {
    pwmVal += pwm_dif;
    if (pwmVal < MIN_PWM || pwmVal > MAX_PWM) {
        return MOTOR_ERROR;
    }
    ledcWrite(pwm_channel, pwmVal);
    return pwmVal;
}

int Motor::set_pwm(unsigned int _pwmVal) {
    if (_pwmVal < 0 || _pwmVal > MAX_PWM) {
        return MOTOR_ERROR;
    }
    ledcWrite(pwm_channel, _pwmVal);
    pwmVal = _pwmVal;
    return MOTOR_SUCCESS;
}