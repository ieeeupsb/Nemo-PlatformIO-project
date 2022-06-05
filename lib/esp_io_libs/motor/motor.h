#pragma once
#if MOTORS

#include "Arduino.h"
#include "ESP32Encoder.h"

#define MIN_PWM 120
#define MAX_PWM 150

#define LEFT_MOTOR_CHANNEL 0
#define RIGHT_MOTOR_CHANNEL 1

#define WALK_CONST 3.43
#define ROTATION_CONST (2120.0 / 360.0)

class Motor {
  public:
    void setup(uint8_t dc_motor_1_pin, uint8_t dc_motor_2_pin,
               uint8_t enable_pin, uint8_t channel, int enc1_pin, int enc2_pin);
    void set_dir_set_pwm(uint8_t _dir, uint32_t _pwmVal);
    void stop();
    ESP32Encoder encoder;
    uint32_t pwmVal;
    uint8_t dir;
    float get_speed();
    int pwm_refresh(int pwm_dif);
    void set_pwm(unsigned int _pwmVal);
    float speed = 0;
    int pwm_average = 0;

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