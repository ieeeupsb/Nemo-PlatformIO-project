#pragma once

#define MAXTIME 10000
#define NEAR_TIME 500

void sonar_setup(int trigPin, int echoPin);

void send_pulse(int trigPin);

float distance(int trigPin, int echoPin);