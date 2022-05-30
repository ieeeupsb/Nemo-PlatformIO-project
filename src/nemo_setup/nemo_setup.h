#pragma once

#include "nemo_pinout.h"
#define PATH_NEMO_MOTION_H "../nemo_motion/nemo_motion.h"

#define ENV ESP32DEV

#if DEBUG_MODE
#define DEBUG_REFRESH_RATE 300
#endif

#define NEMO_PWM 140   // 140
#define MAX_SPEED 0.5  // 0.5
#define MIN_SPEED 0.25 // 0.25

#define USE_WIFI 0
#if USE_WIFI
#define UDP_ADDRESS                                                            \
    "192.168.1.43" // "192.168.120.187" //"192.168.0.116" // Comp server ip
#define UDP_PORT 44832U
#endif

#define ELECTROMAGNET_ON digitalWrite(ELECTROMAGNET, HIGH)
#define ELECTROMAGNET_OFF digitalWrite(ELECTROMAGNET, LOW)
#define ELECTROMAGNET_SETUP pinMode(ELECTROMAGNET, OUTPUT)

void nemo_line_setup();
