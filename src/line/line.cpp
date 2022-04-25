#include "line.h"

#include "../communication/comm.h"
#include "../src/setup.h"
#include <Arduino.h>

// #define LINE_SENSOR_1 GPIO36
// #define LINE_SENSOR_2 GPIO39
// #define LINE_SENSOR_3 GPIO34
// #define LINE_SENSOR_4 GPIO35

void line_setup() {
    pinMode(LINE_SENSOR_1, INPUT);
    pinMode(LINE_SENSOR_2, INPUT);
    pinMode(LINE_SENSOR_3, INPUT);
    pinMode(LINE_SENSOR_4, INPUT);
}

int line_case_debug() {
    switch (LINE_CASE_FAST) {
    case CORRECT_TO_RIGHT:
        debug_message("CORRECT_TO_RIGHT");
        break;
    case CORRECT_TO_LEFT:
        debug_message("CORRECT_TO_RIGHT");
        break;
    case RIGHT_CURVE:
        debug_message("RIGHT_CURVE");
        break;
    case LEFT_CURVE:
        debug_message("LEFT CURVE");
        break;
    case INTERCEPTION:
        debug_message("INTERCEPTION");
        break;
    case LINE:
        debug_message("LINE");
        break;
    case FREE:
        debug_message("FREE");
        break;
    default:
        debug_message("ERROR");
        return -1;
    }

    return LINE_CASE_FAST;
}