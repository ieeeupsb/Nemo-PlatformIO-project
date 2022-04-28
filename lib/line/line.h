#pragma once

#include <Arduino.h>

#define CORRECT_TO_RIGHT 4  // NEED TO TURN RIGHT 0010
#define CORRECT_TO_LEFT 128 // NEED TO TURN LEFT 0100
#define RIGHT_CURVE 144     // 0111
#define LEFT_CURVE 12       // 1110
#define INTERCEPTION 156    // 1111
#define LINE 132            // 0110
#define FREE 0              // 0000

#define line_state(__LINE_SENSOR__) (digitalRead(__LINE_SENSOR__))
#define LINE_CASE_FAST                                                         \
    (GPIO.in1.val & 0x9C) // GPIO.in1.val & 0x9C = L200L1 L4L300

// 35 39 34 36
// L1 L2 L3 L4

// 32 33 ...40

// shift
// 3  7  2  4
// L1 L2 L3 L4

// 8 7  6 5 4  3  2  1 0
// 0 L2 0 0 L4 L1 L3 0 0
// 0 1  0 0 1  1  1  0 0

void line_setup();
int line_case_debug();