/**
 * @file motion.h
 * @author ManelMCCS
 * @brief
 * @version 1.1
 * @date 2022-06-06
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "pid.h"
#include "pin_wiring.h"
#include "wheel.h"

typedef enum { DIR_NOT_DEF = 0,
               FORWARD,
               BACKWARDS } motion_direction_t;

/**
 * @brief Class that keeps the robot's movement state and controls it
 *
 */
class Motion {
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
     * @brief make robot walk with a certain direction distance or speed_ms.
     * Non-blocking function;
     *
     * @param millimeters robot max travelled distance after function
     * call. Non-blocking function
     * @param direction robot direction. use FORWARD or BACKWARDS
     * @param speed_ms intended robot speed_ms in m/s
     */
    void walk(motion_direction_t direction);
    void walk(motion_direction_t direction, unsigned speed_ms);

    void set_max_distance(unsigned distance_mm);
    void set_speed_ms(motion_direction_t direction, unsigned speed_ms);

    void rotate_degrees(int degrees, int direction, long unsigned speed_ms);
    /**
     * @brief Update current speed_ms measurement and stop the motors if
     * standstill conditions are met
     */
    void refresh();
    float linear_speed_update();

    /**
     * @brief Construct a new test motors object. Max speed on both motor for 200 miliseconds.
     *
     */
    void test_motors();

    /**
     * @brief Tests if encoders are working. Set max speed until the robot reach the 200 mm.
     *
     */
    void test_encoders();

  private:
    Wheel left_wheel;
    Wheel right_wheel;
    Pid pid;
};