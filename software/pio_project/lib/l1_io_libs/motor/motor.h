
#pragma once
/**
 * @file motor.h
 * @author manel
 * @brief
 * @version 0.1
 * @date 2022-06-06
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <ports.h>

#ifndef MIN_PWM
#define MIN_PWM 0
#endif
#ifndef MAX_PWM
#define MAX_PWM 255
#endif

typedef enum { MOTOR_ERROR = 0,
               MOTOR_SUCCESS } motor_return_t;

/**
 * @brief Motor direction flags
 *
 */
typedef enum { ROTATION_NOT_DEFINED = 0,
               CLOCKWISE,
               ANTI_CLOCKWISE } motor_rotation_dir_t;

/**
 * @brief Motor is a class that contains motor function data and controls the DC
 * motor through the signals from the encoders.
 *
 */
class Motor {
  public:
    void setup(uint8_t dc_motor_1_pin, uint8_t dc_motor_2_pin,
               uint8_t enable_pin, uint8_t pwm_channel);
    /**
     * @brief Stops the motor (sets pwm to 0)
     *
     */
    void stop();

    uint32_t pwm_val = 0;

    void set_direction(motor_rotation_dir_t motor_rotation_dir);
    int pwm_offset(int pwm_dif);
    motor_return_t set_pwm(unsigned int _pwmVal);

    int get_pwm();

  private:
#if ESP32
    uint8_t pwm_channel;
    double pwm_frequency = 5000;
    uint8_t resolution_bits = 8;
#endif

    uint8_t dc_motor_1;
    uint8_t dc_motor_2;

    float previous_tick_number = 0;
    float previous_time = 0;
};
