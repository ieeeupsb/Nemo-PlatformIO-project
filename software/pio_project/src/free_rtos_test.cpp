/////////////////////////////////////////////////////////////////

#include "Arduino.h"
#include "SimpleFSM.h"

/////////////////////////////////////////////////////////////////

SimpleFSM fsm;

/////////////////////////////////////////////////////////////////

void on_red() {
    Serial.println("State: RED");
}

void on_green() {
    Serial.println("State: GREEN");
}

/////////////////////////////////////////////////////////////////

State s[] = {
    State("red", on_red),
    State("green", on_green)};

TimedTransition timedTransitions[] = {
    TimedTransition(&s[0], &s[1], 6000),
    TimedTransition(&s[1], &s[0], 4000),
};

int num_timed = sizeof(timedTransitions) / sizeof(TimedTransition);

/////////////////////////////////////////////////////////////////

void setup() {
    Serial.begin(9600);
    while (!Serial) {
        delay(300);
    }
    Serial.println();
    Serial.println("SimpleFSM - Timed Transition (Simple traffic light)\n");

    fsm.add(timedTransitions, num_timed);
    fsm.setInitialState(&s[0]);
}

/////////////////////////////////////////////////////////////////

void loop() {
    fsm.run();
}

/////////////////////////////////////////////////////////////////