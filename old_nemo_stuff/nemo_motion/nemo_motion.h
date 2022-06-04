#pragma once

#include <line.h>
#include <motor.h>
#include <nemo_communications.h>
#include <nemo_pinout.h>
#include <nemo_setup.h>
#include <sonar.h>

void motors_setup();

void walk_line(int millimeters, int direction, int turn);
void rotate(int degrees, int direction, int speed);
int rotate_line(int degrees, int direction, int speed);
void correct_trajectory();
void correct_trajectory_line();
void correct_trajectory_line_1();
void pid_control(int direction);
void andamento(int millimeters, int direction);
void andamento_linha(int direction, int turn);
void pid(int direction);
void pid_speed(int direction);
void walk(int millimeters, int direction);