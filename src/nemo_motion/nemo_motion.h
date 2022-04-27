#pragma once

#define MIN_SPEED 5

void motors_setup();

void walk_line(int millimeters, int direction, int turn);
void rotate(int degrees, int direction, int speed);
int rotate_line(int degrees, int direction, int speed);
void correct_trajectory();
void correct_trajectory_line();