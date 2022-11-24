#include "sonar_HC_SR04.h"

Sonar_HC_SR04::Sonar_HC_SR04nar(uint8_t trig_pin, uint8_t echo_pin) {
    set_trig_pin(trig_pin);
    set_echo_pin(echo_pin);
}

int Sonar_HC_SR04::measure_distance() {
    digitalWrite(this->trig_pin, LOW);
    delayMicroseconds(2);
    // Sets the this->trig_pin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(this->trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->trig_pin, LOW);
    // Reads the this->echo_pin, returns the sound wave travel time in microseconds
    duration = pulseIn(this->echo_pin, HIGH);
    // Calculating the distance
    return duration * 0.034 / 2;
}

void Sonar_HC_SR04::set_trig_pin(uint8_t new_trig_pin) {
    pin_mode(new_trig_pin, OUTPUT)
}
void Sonar_HC_SR04::set_echo_pin(uint8_t new_echo_pin) {
    pin_mode(new_echo_pin, INPUT)
}