#include "motor.h"

#ifndef MIN_PWM
#define MIN_PWM 0
#endif
#ifndef MAX_PWM
#define MAX_PWM 255
#endif
/**
 * \def
 * @brief 3.43 encoder ticks represents 1 mm
 */
#define WALK_CONST 3.43
#define ROTATION_CONST_DEGREES (2120.0 / 360.0)

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
 * @brief
 *
 * @param _dir
 * @param _pwmVal
 */

void Motor::set_dir_set_pwm(uint8_t _dir, uint32_t _pwmVal) {
    ledcWrite(pwm_channel, _pwmVal);
    digitalWrite(dc_motor_1, _dir);
    digitalWrite(dc_motor_2, !_dir);

    pwmVal = _pwmVal;
    dir = _dir;
}

void Motor::stop() {
    ledcWrite(pwm_channel, 0);
    digitalWrite(dc_motor_1, LOW);
    digitalWrite(dc_motor_2, LOW);
}
/**
 * @brief Refresh current_speed variable and return the robot speed
 *
 * @return float
 */
float Motor::get_speed() {
    float current_tick_number = (float)encoder.getCount();
    float current_time = (float)millis();
    float distance = (current_tick_number - previous_tick_number) * WALK_CONST;
    float time = (current_time - previous_time);

    if (!distance || !time) // if the distance or the time diference is zero
                            // acelaration is zero
        return Motor::current_speed;

    Motor::current_speed = distance / time;

    // Refresh previous_vars in the end of the function
    previous_tick_number = encoder.getCount();
    previous_time = millis();

    return Motor::current_speed;
}
int Motor::pwm_refresh(int pwm_dif) {
    pwmVal += pwm_dif;
    if (pwmVal < MIN_PWM || pwmVal > MAX_PWM) {
        return -1;
    }
    ledcWrite(pwm_channel, pwmVal);
    return pwmVal;
}
void Motor::set_pwm(unsigned int _pwmVal) {
    if (_pwmVal < 0 || _pwmVal > MAX_PWM) {
        return;
    }
    ledcWrite(pwm_channel, _pwmVal);
    pwmVal = _pwmVal;
}