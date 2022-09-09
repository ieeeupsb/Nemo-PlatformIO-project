#include "wheel.h"

// FIXME WRONG VALUE
#define WHEEL_RADIUS 34

/**
 * \def
 * @brief 3.43 encoder ticks represents 1 mm
 */
#define TICKS_MM_RATIO 3.43;

#define ROTATION_CONST_DEGREES (2120.0 / 360.0)

void Wheel::setup(uint8_t dc_motor_1_pin, uint8_t dc_motor_2_pin,
                  uint8_t enable_pin, uint8_t pwm_channel, int enc1_pin,
                  int enc2_pin) {

    motor.setup(dc_motor_1_pin, dc_motor_2_pin, enable_pin, pwm_channel);
    encoder.attachHalfQuad(enc1_pin, enc2_pin); // seting up the motor enconder
}

// TODO: test this function
bool Wheel::is_max_distance() {
    bool ret = (user_max_enconder_ticks == encoder.getCount());
    return ret;
}

// TODO: test this function
void Wheel::set_max_distance(int distance_mm) {
    user_max_enconder_ticks = (float)distance_mm * TICKS_MM_RATIO;
}

void Wheel::set_max_speed() {
    motor.set_pwm(MAX_PWM);
}

void Wheel::stop() {
    motor.stop();
}