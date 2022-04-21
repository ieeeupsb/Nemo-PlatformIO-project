#pragma once

#define CORRECT_TO_RIGHT 4      // NEED TO TURN RIGHT
#define CORRECT_TO_LEFT 16    //NEED TO TURN LEFT
#define RIGHT_CURVE 144     // 0111
#define LEFT_CURVE 12     // 1110
#define INTERCEPTION 156   // 1111
#define LINE 132
#define FREE 0            // 0000

#define line_state(__LINE_SENSOR__) (digitalRead(__LINE_SENSOR__))
#define LINE_CASE_FAST GPIO.in1.val & 0x9C // GPIO.in1.val & 0x9C = L200L1 L4L300

void line_setup();
void line_case_debug();