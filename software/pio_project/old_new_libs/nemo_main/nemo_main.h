#pragma once

#include "nemo.h"

Nemo nemo;

#define NON_BLOCKING_DELAY_MS(__DO_SOMETHING__, __WAIT_TIME_MS__) \
    {                                                             \
        static unsigned long last_time = 0;                       \
        if ((millis() - last_time) > __WAIT_TIME_MS__) {          \
            __DO_SOMETHING__;                                     \
            last_time = millis();                                 \
        }                                                         \
    }

void LeftEncoderInterruptHandler() {
    left_wheel.EncoderInterruptHandler();
}

void RightEncoderInterruptHandler() {
    right_wheel.EncoderInterruptHandler();
}

inline void attach_all_interrupts() {
    attachInterrupt(digitalPinToInterrupt(ENC1_L), LeftEncoderInterruptHandler, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENC1_R), RightEncoderInterruptHandler, CHANGE);
}

void nemo_setup() {
}

void nemo_loop() {
    NON_BLOCKING_DELAY_MS(LeftEncoderInterruptHandler(), 500);
    NON_BLOCKING_DELAY_MS(RightEncoderInterruptHandler(), 500);
}