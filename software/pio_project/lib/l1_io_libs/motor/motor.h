
#pragma once
/**
 * @file motor.h
 * @author Manuel Cerqueira da Silva and Vinícius Pirassoli.
 * @brief Library to control Nemo DC Motors.
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

/**
 * @brief Motor return type to handle errors using the Motor class.
 *
 */
typedef enum { MOTOR_ERROR = 0,
               MOTOR_SUCCESS } motor_return_t;

/**
 * @brief Motor direction flags type.
 *
 */
typedef enum { ROTATION_NOT_DEFINED = 0,
               CLOCKWISE,
               ANTI_CLOCKWISE } motor_rotation_dir_t;

// WARN
/**
 * @brief PWM variable type.
 *
 * PWM range is 0 to 255, store in a 8 bit unsigned integer.
 *
 */
typedef uint8_t pwm_t;

// FIXME
/**
 * @brief Motor is a class used for controling a DC Motor.
 *
 * This class stores the motors pins and the motor **não sei que termo usar, help** via PWM (0-255).
 * Each motor have 3 pins:
 *    The DC motor enable pin to control the motor the **o mesmmo problema de cima**
 *    The 2 DC motor terminal pins to control and current flow in the motor and consequently the rotation direction.
 *
 */
class Motor {
  public:
    void setup(uint8_t dc_motor_1_pin, uint8_t dc_motor_2_pin,
               uint8_t enable_pin, uint8_t pwm_channel);

    /**
     * @brief Stops the motor (sets PWM to 0)
     *
     */
    void stop();

    /**
     * @brief Set the motor rotation direction. The allowed values are CLOCKWISE and ANTI_CLOCKWISE.
     *
     * @param motor_rotation_dir
     */
    void set_rotation_dir(motor_rotation_dir_t motor_rotation_dir);

    /**
     * @brief Set the a PWM given by the user and stores the value.
     *
     * If the PWM given is not in the valid range this method returns MOTOR_ERROR. Otherwise returns MOTOR_SUCCESS.
     *
     * @param pwm_val
     * @return motor_return_t
     */
    motor_return_t set_pwm(pwm_t pwm_val);

    /**
     * @brief Increase or decrease the PWM value by the offset value.
     *
     * @param offset_val
     * @return motor_return_t
     */
    motor_return_t pwm_offset(pwm_t offset_val);

    /**
     * @brief Get the PWM value from the motor.
     *
     * @return pwm_t
     */
    pwm_t get_pwm();

  private:
    /**
     * @brief Last PWM value given to the motor enable analog pin.
     *
     * This is variable is set to private to prevent changing only the variable and not the real Motor PWM.
     * For change motor PWM value use pwm_offset and the set_pwm  Motor's methods.
     * For check the current pwm value outside of this library you should use the get_pwm Motor's method.
     *
     */
    pwm_t current_pwm = 0;
#if ESP32
    // For using the analog pins with the ESP32 it is necessary to configure a PWM channel.

    uint8_t pwm_channel;
    double pwm_frequency = 5000;
    uint8_t resolution_bits = 8;
#endif
    /**
     * @brief DC motor digital pin number 1 used to control the current flow inside the motor.
     *
     */
    uint8_t dc_motor_1;

    /**
     * @brief DC motor digital pin number 1 used to control the current flow inside the motor.
     *
     */
    uint8_t dc_motor_2;
};
