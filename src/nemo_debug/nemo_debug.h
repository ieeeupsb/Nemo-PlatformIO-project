#pragma once

#include "nemo_setup/nemo_setup.h"

#include <Arduino.h>
#include <comm.h>
#include <line.h>
#include <motor.h>

#define DEBUG_SPEED                                                            \
    {                                                                          \
        char aux[128];                                                         \
        sprintf(aux, "Left speed %f: Right speed %f \n",                       \
                left_motor.get_speed(), right_motor.get_speed());              \
        debug_message(aux);                                                    \
    }

void debug_message(const char *message);
void debug_encoder(Motor m);
int line_case_debug();
void debug_motor(Motor m, int time);