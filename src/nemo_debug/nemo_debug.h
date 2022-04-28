#pragma once

#include "../line/line.h"
#include "../setup.h"
#include <Arduino.h>
#include <comm.h>
#include <motor.h>

void debug_message(const char *message);
void debug_encoder(Motor m);
int line_case_debug();
void debug_motor(Motor m, int time);