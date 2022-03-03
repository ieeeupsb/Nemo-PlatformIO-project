#include "sonar.h"

#include "setup.h"
#include "Arduino.h"


void sonar_setup() {
    pinMode(SONAR_TRIG, OUTPUT);
    pinMode(SONAR_ECHO, INPUT);
}