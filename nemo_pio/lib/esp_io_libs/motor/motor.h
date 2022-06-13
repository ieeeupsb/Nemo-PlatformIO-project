#if MOTORS

#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"
#include "ESP32Encoder.h"

#include "nemo_global_macros.h"
#pragma message("using global macros in motor.h for test reasons")

class Motor {
  public:
    ESP32Encoder encoder;

    void setup(uint8_t dc_motor_1_pin, uint8_t dc_motor_2_pin,
               uint8_t enable_pin, uint8_t channel, int enc1_pin, int enc2_pin);
    void stop();

    uint8_t dir;
    uint32_t pwmVal;
    void set_dir_set_pwm(uint8_t _dir, uint32_t _pwmVal);
    int pwm_refresh(int pwm_dif);
    void set_pwm(unsigned int _pwmVal);

    float current_speed = 0;
    float get_speed();

  private:
    uint8_t pwm_channel;
    double pwm_frequency = 5000;
    uint8_t resolution_bits = 8;

    uint8_t dc_motor_1;
    uint8_t dc_motor_2;

    float previous_tick_number = 0;
    float previous_time = 0;
};

#endif
#endif