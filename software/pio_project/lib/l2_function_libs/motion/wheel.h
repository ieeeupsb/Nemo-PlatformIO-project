/**
 * @file nemo_motion.h
 * @author ManelMCCS
 * @brief
 * @version 1.1
 * @date 2022-06-06
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "ESP32Encoder.h"
#include "motor.h"

/**
 * @brief Class that contains motor function data and controls the DC
 * motor through the signals from the encoders.
 *
 */
class Wheel {
  private:
    ESP32Encoder encoder;
    Motor motor;

    unsigned int user_max_enconder_ticks;

  public:
    float linear_speed = 0;
    float angular_speed = 0;

    /**
     * @brief Wheel setup (dc motor + encoder)
     *
     */
    void setup(uint8_t dc_motor_1_pin, uint8_t dc_motor_2_pin,
               uint8_t enable_pin, uint8_t pwm_channel, int enc1_pin,
               int enc2_pin);

    /**
     * @brief Stop both wheels
     *
     */
    void stop();

    void set_max_distance(int distance_mm);
    bool is_max_distance();

    float linear_speed_update();

    /**
     * @brief Set the max speed to motor.
     *
     */
    void set_max_speed();
    void increase_speed();
    void decrease_speed();

    float current_speed_ms = 0;
    /**
     * @brief Refresh current_speed_ms variable for the motor and return the motor
     * speed
     *
     * @return float Motor::current_speed_ms
     */
    float get_speed_ms();
};