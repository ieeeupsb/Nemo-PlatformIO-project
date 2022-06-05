#pragma once

#include <nemo_setup.h>

#include <nemo_motion.h>

#include "colour_code/colour_code.h"
#include "positioning/positioning.h"
#include <comm.h>
#include <line.h>
#include <motor.h>
#include <nemo_communications.h>
#include <sonar.h>

#define BLUE_LEVEL 1
#define GREEN_LEVEL 2
#define RED_LEVEL 3

#define N_BOXES 4
#define LEVEL BLUE_LEVEL

int main_function();