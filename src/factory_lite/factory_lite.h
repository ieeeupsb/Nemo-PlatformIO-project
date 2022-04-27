#pragma once

#include "setup.h"

#include "../eletromagnet/eletromagnet.h"
#include "../line/line.h"
#include "../nemo_debug/nemo_debug.h"
#include "../nemo_motion/nemo_motion.h"
#include "../sonar/sonar.h"
#include "colour_code/colour_code.h"
#include "positioning/positioning.h"
#include <comm.h>
#include <motor.h>

#define BLUE_LEVEL 1
#define GREEN_LEVEL 2
#define RED_LEVEL 3

#define NEMO_SPEED 170 // 0-255
#define N_BOXES 4
#define LEVEL BLUE_LEVEL

int factory_lite();
void recieve_colour_code(char *colour_code, char local, const char *udpAddress);