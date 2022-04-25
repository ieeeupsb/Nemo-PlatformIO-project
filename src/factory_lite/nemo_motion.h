#pragma once

void motors_setup();

void walk(int millimeters, int direction, int turn);
void rotate(int degrees, int direction, int speed);