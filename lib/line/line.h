#pragma once

#include <Arduino.h>

// L4 will be the oposite of the others, need to negate

#define CORRECT_TO_RIGHT 12 // NEED TO TURN RIGHT 0010  //0011
#define CORRECT_TO_LEFT 136 // NEED TO TURN LEFT 0100   //0101
#define RIGHT_CURVE 156  // 0111                     //0110  //estavam trocados
#define LEFT_CURVE 132   // 1110                     //1111  //estavam trocados
#define INTERCEPTION 148 // 1111                     //1110
#define LINE 140         // 0110                     //0111
#define FREE 8           // 0000                     //0001

#define line_state(__LINE_SENSOR__) (digitalRead(__LINE_SENSOR__))
#define LINE_CASE_FAST                                                         \
    (GPIO.in1.val & 0b10011100) // GPIO.in1.val & 0b10011100 = L200L1 L4L300

void line_setup();
int line_case_debug();