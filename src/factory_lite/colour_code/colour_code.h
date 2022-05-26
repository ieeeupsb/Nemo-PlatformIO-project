#pragma once

#include "../../nemo_setup/nemo_setup.h"
#include <comm.h>

#define N_BOXES 4

void recieve_colour_code(char *colour_code, char local, const char *ip_address);