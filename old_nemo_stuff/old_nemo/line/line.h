#pragma once

#include <Arduino.h>

// L4 will be the oposite of the others, need to negate

#define CORRECT_TO_RIGHT 24 // NEED TO TURN RIGHT 0010  //0011
#define CORRECT_TO_LEFT 136 // NEED TO TURN LEFT 0100   //0101
#define SHARP_LEFT 12       // NEED TO TURN LEFT 0100   //0101
#define SHARP_RIGHT 0
#define RIGHT_CURVE 156  // 0111                     //0110  //estavam trocados
#define LEFT_CURVE 144   // 1110                     //1111  //estavam trocados
#define INTERCEPTION 148 // 1111                     //1110
#define LINE 152         // 0110                     //0111
#define FREE 8           // 0000                     //0001

#define line_state(__LINE_SENSOR__) (digitalRead(__LINE_SENSOR__))
#define LINE_CASE_FAST                                                         \
    (GPIO.in1.val & 0b10011100) // GPIO.in1.val & 0b10011100 = L200L1 L4L300

#define PRINT_SENSOR                                                           \
    Serial.print((LINE_CASE_FAST >> 4) & 1);                                   \
    Serial.print(" ");                                                         \
    Serial.print((LINE_CASE_FAST >> 7) & 1);                                   \
    Serial.print(" ");                                                         \
    Serial.print((LINE_CASE_FAST >> 2) & 1);                                   \
    Serial.print(" ");                                                         \
    Serial.println((LINE_CASE_FAST >> 3) & 1);

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