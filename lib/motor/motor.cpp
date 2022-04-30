#include "motor.h"
#include <ESP32Encoder.h>

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

void Motor::set_speed(uint8_t _dir, uint32_t _pwmVal) {
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

float Motor::get_speed() {
    float current_tick_number = (float)encoder.getCount();
    float current_time = (float)millis();
    float distance = (current_tick_number - previous_tick_number) / WALK_CONST;
    float time = (current_time - previous_time);

    if (!distance || !time)
        return speed;

    float speed = distance / time;
    // Refresh previous_vars in the end of the function
    previous_tick_number = encoder.getCount();
    previous_time = millis();

    return speed;
}
/*ultimas duas  não testadas*/
void Motor::refresh(int pwm_dif) {
    pwmVal += pwm_dif;
    if (pwmVal < 0 || pwmVal > MAX_PWM) {
        return;
    }
    ledcWrite(pwm_channel, pwmVal);
}
void Motor::set_pwm(unsigned int _pwmVal) {
    if (_pwmVal < 0 || _pwmVal > 255) {
        return;
    }
    ledcWrite(pwm_channel, _pwmVal);
    pwmVal = _pwmVal;
}