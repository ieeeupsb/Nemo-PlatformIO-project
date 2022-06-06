#pragma once

#include "motor.h"
#include "nemo_pinout.h"

class Pid {
    int p, i, d;
};
/**
 * @brief
 *
 */
class motion {
  public:
    float linear_speed = 0;
    float angular_speed = 0;

    void setup();
    void walk_distance(int millimeters, int direction, int turn);
    void rotate_degrees(int degrees, int direction, int speed);
    void motion_refresh();
    float linear_speed_update();

  private:
    Motor left_motor;
    Motor right_motor;
    Pid pid;
};
