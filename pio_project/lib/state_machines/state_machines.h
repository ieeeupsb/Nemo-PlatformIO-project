#pragma once

#include "micro_controller_unit.h"
#include <PID_v1.h>

enum class update_speed_state {
    STATE_1 = 0,
    STATE_2,
};

enum class motion_controller_state {
    STATE_1 = 0,
    STATE_2,
};

enum class serial_data_state {
    STATE_1 = 0,
    STATE_2,
};

MicroControllerUnit &mcu = MicroControllerUnit::getInstance();
void update_speed_sm() {

    update_speed_state = update_speed_state::STATE_1

        switch (state1) {
    case LED1_ON:
        digitalWrite(led1, HIGH);
        state1 = LED1_OFF;
        break;
    case LED1_OFF:
        digitalWrite(led1, LOW);
        state1 = LED1_ON;
        break;
    }
}

void robot_motion_controller_sm() {
    while (1) {
        /* Perform machine 2 task */
        printf("Machine 2 is running...\n");
        vTaskDelay(pdMS_TO_TICKS(MACHINE2_DELAY));
    }
}

void serial_data_sm() {
    while (1) {
        /* Perform machine 1 task */
        printf("Machine 1 is running...\n");
        vTaskDelay(pdMS_TO_TICKS(MACHINE1_DELAY));
    }
}

#include <Arduino.h>

const int led1 = 13;
const int led2 = 12;
const int led3 = 11;

enum State1 {
    LED1_ON,
    LED1_OFF
};

enum State2 {
    LED2_ON,
    LED2_OFF
};

enum State3 {
    LED3_ON,
    LED3_OFF
};

State1 state1 = LED1_OFF;
State2 state2 = LED2_OFF;
State3 state3 = LED3_OFF;

void stateMachine1() {
    switch (state1) {
    case LED1_ON:
        digitalWrite(led1, HIGH);
        state1 = LED1_OFF;
        break;
    case LED1_OFF:
        digitalWrite(led1, LOW);
        state1 = LED1_ON;
        break;
    }
}

void stateMachine2() {
    switch (state2) {
    case LED2_ON:
        digitalWrite(led2, HIGH);
        state2 = LED2_OFF;
        break;
    case LED2_OFF:
        digitalWrite(led2, LOW);
        state2 = LED2_ON;
        break;
    }
}

void stateMachine3() {
    switch (state3) {
    case LED3_ON:
        digitalWrite(led3, HIGH);
        state3 = LED3_OFF;
        break;
    case LED3_OFF:
        digitalWrite(led3, LOW);
        state3 = LED3_ON;
        break;
    }
}

void setup() {
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
}

void loop() {
    stateMachine1();
    stateMachine2();
    stateMachine3();
    delay(1000);
}