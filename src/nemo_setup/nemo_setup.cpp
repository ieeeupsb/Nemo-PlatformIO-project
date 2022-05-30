#include "nemo_setup.h"

#include <Arduino.h>

void nemo_line_setup() {
    pinMode(LINE_SENSOR_1, INPUT);
    pinMode(LINE_SENSOR_2, INPUT);
    pinMode(LINE_SENSOR_3, INPUT);
    pinMode(LINE_SENSOR_4, INPUT);
}