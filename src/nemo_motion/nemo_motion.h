#pragma once

#include "../line/line.h"
#include "../nemo_debug/nemo_debug.h"
#include "../setup.h"
#include <motor.h>



extern Motor left_motor;
extern Motor right_motor;

void motors_setup();

void walk_line(int millimeters, int direction, int turn);
void rotate(int degrees, int direction, int speed);
int rotate_line(int degrees, int direction, int speed);
void correct_trajectory();
void correct_trajectory_line();