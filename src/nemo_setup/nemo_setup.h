#pragma once

#include "nemo_pinout.h"

#define ENV ESP32DEV
#define MODE FACTORY_LITE

#define DEBUG_MODE true
#define DEBUG_REFRESH_RATE 300

#define BAUD_RATE 115200

#define NEMO_PWM 140   // 140
#define MAX_SPEED 0.5  // 0.5
#define MIN_SPEED 0.25 // 0.25

#define USE_WIFI true
#define UDP_ADDRESS                                                            \
    "192.168.1.43" // "192.168.120.187" //"192.168.0.116" // Comp server ip
#define UDP_PORT 44832U

#define ELECTROMAGNET_ON digitalWrite(ELECTROMAGNET, HIGH)
#define ELECTROMAGNET_OFF digitalWrite(ELECTROMAGNET, LOW)
#define ELECTROMAGNET_SETUP pinMode(ELECTROMAGNET, OUTPUT)

inline void nemo_line_setup();
