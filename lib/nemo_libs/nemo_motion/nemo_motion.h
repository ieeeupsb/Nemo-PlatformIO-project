#ifndef NEMO_MOTION_H
#define NEMO_MOTION_H
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
#include "motor.h"
#include "nemo_pinout.h"

class Pid {
    int p, i, d;
};
/**
 * @brief Class that keeps the robot's movement state and controls it
 *
 */
class motion {
  public:
    float linear_speed = 0;
    float angular_speed = 0;

    /**
     * @brief Setup the left and right nemo wheels motors
     *
     */
    void setup();
    /**
     * @brief Stop both wheels
     *
     */
    void stop();
    // TODO : overload functions not implemented
    /**
     * @brief make robot walk with a certain direction distance or speed.
     * Non-blocking function;
     *
     * @param millimeters robot max travelled distance after function
     * call. Non-blocking function
     * @param direction robot direction. use FORWARD or BACKWARDS
     * @param speed intended robot speed in m/s
     */
    void walk(int direction);
    void walk(int direction, unsigned speed);

    /**
     * @brief Writes the pwm directly to the driver to control the left and right motors
     *
     * @param pwm_left value to set the left motor pwm (0 to 255)
     * @param pwm_right value to set the right motor pwm (0 to 255)
     */
    void simple_walk(int pwm_left, int pwm_right);

    void set_max_distance(unsigned distance_mm);

    void rotate_degrees(int degrees, int direction, long unsigned speed);
    /**
     * @brief Update current speed measurement and stop the motors if
     * standstill conditions are met
     */
    void refresh();
    float linear_speed_update();

  private:
    Motor left_motor;
    Motor right_motor;
    Pid pid;
    /**
     * @brief maximum number of ticks for a given distance
     * or rotation
     *
     */
    int max_ticks;
};

#endif