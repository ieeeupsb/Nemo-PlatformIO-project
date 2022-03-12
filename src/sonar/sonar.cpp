#include "sonar.h"

#include "setup.h"

#include "Arduino.h"
#include "wiring_private.h"
#include <stdint.h>

void sonar_setup() {
    pinMode(SONAR_TRIG_1, OUTPUT);
    pinMode(SONAR_TRIG_2, OUTPUT);
    pinMode(SONAR_ECHO_1, INPUT);
    pinMode(SONAR_ECHO_2, INPUT);
}

void send_pulse(int trigPin) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(1);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
}

float distance(int trigPin, int echoPin) {
    send_pulse(trigPin);
    return pulseIn(echoPin, HIGH)/2*0.0343;
} 