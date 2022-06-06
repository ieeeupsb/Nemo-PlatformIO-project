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
    void walk_distance(int millimeters, int direction, int turn);
    void rotate_degrees(int degrees, int direction, int speed);
    /**
     * @brief Refresh current robot speed and stop the motors at
     * standstill conditions
     *
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