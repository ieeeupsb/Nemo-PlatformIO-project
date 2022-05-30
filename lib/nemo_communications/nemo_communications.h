#if DEBUG_MODE

#ifndef NEMO_DEBUG_H
#define NEMO_DEBUG_H

#define print_message(x)                                                       \
    {                                                                          \
        char aux[128];                                                         \
        sprintf(aux, x);                                                       \
        send_message(aux);                                                     \
    }

#include "../nemo_setup/nemo_setup.h"
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

#endif
#else

#define debug_message(empty)
#define print(empty)
#define DEBUG_SPEED                                                            \
    {}

#endif