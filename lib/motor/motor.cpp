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

void Motor::set_speed(uint8_t dir, uint32_t pwmVal) {
    ledcWrite(pwm_channel, pwmVal);
    digitalWrite(dc_motor_1, dir);
    digitalWrite(dc_motor_2, !dir);
}

void Motor::stop() {
    ledcWrite(pwm_channel, 0);
    digitalWrite(dc_motor_1, LOW);
    digitalWrite(dc_motor_2, LOW);
}