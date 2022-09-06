
#ifndef MOTOR_H
#define MOTOR_H

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

#include "Arduino.h"
#include "ESP32Encoder.h"

#include "nemo_global_macros.h"
// TODO: using global macros in motor.h for test reasons

typedef enum { MOTOR_ERROR = 0,
               MOTOR_SUCCESS } motor_return_t;

/**
 * @brief Motor direction flags
 *
 */
typedef enum { DIR_NOT_DEF = 0,
               FORWARD,
               BACKWARDS } motor_direction_t;

/**
 * \def
 * @brief 3.43 encoder ticks represents 1 mm
 */
#define WALK_CONST 3.43

#define ROTATION_CONST_DEGREES (2120.0 / 360.0)

/**
 * @brief Motor is a class that contains motor function data and controls the DC
 * motor through the signals from the encoders.
 *
 */
class Motor {
  public:
    ESP32Encoder encoder;

    void setup(uint8_t dc_motor_1_pin, uint8_t dc_motor_2_pin,
               uint8_t enable_pin, uint8_t channel, int enc1_pin, int enc2_pin);
    /**
     * @brief Stops the motor (sets pwm to 0)
     *
     */
    void stop();

    uint8_t dir = DIR_NOT_DEF;
    uint32_t pwm_val = 0;

    motor_return_t set_direction(motor_direction_t _dir);
    int pwm_offset(int pwm_dif);
    int set_pwm(unsigned int _pwmVal);

    int get_pwm();

    float current_speed_ms = 0;
    /**
     * @brief Refresh current_speed_ms variable for the motor and return the motor
     * speed
     *
     * @return float Motor::current_speed_ms
     */
    float get_speed_ms();

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