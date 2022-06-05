#include "sonar.h"
#include "Arduino.h"
#include "wiring_private.h"
#include <stdint.h>

void send_pulse(int trigPin) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(60);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(trigPin, LOW);
}

float distance(int trigPin, int echoPin) {
    send_pulse(trigPin);
    return (pulseIn(echoPin, HIGH) / 2 * 0.0343);
}

void sonar_setup(int trigPin, int echoPin) {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}