#pragma once

#include "positioning.h"
#include "setup.h"

#include "../eletromagnet/eletromagnet.h"
#include "../line/line.h"
#include "../nemo_debug/nemo_debug.h"
#include "../nemo_motion/nemo_motion.h"
#include "../sonar/sonar.h"
#include <comm.h>
#include <motor.h>

#define NEMO_SPEED 170 // 0-255

int factory_lite();
void recieve_colour_code(char *colour_code, char local, const char *ip_address);