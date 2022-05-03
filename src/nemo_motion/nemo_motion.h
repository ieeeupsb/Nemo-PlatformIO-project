#pragma once

#include "../line/line.h"
#include "../nemo_debug/nemo_debug.h"
#include "../setup.h"
#include "../sonar/sonar.h"
#include <motor.h>

#define DEBUG_SPEED                                                            \
    {                                                                          \
        char aux[128];                                                         \
        sprintf(aux, "Left speed %f: Right speed %f \n",                       \
                left_motor.get_speed(), right_motor.get_speed());              \
        debug_message(aux);                                                    \
    }

extern Motor left_motor;
extern Motor right_motor;

void motors_setup();

void walk_line(int millimeters, int direction, int turn);
void walk_sonar(int millimeters, int direction);
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