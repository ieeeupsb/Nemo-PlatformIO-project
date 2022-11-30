#include "sonar_HC_SR04.h"

void set_trig_pin(uint8_t new_trig_pin) {
    pin_mode(new_trig_pin, OUTPUT);
}
void set_echo_pin(uint8_t new_echo_pin) {
    pin_mode(new_echo_pin, INPUT);
}

Sonar_HC_SR04::Sonar_HC_SR04(uint8_t trig_pin, uint8_t echo_pin) {
    set_trig_pin(trig_pin);
    set_echo_pin(echo_pin);
}

void send_pulse(int trig_pin) {
    digital_write(trig_pin, LOW);
    delayMicroseconds(60);
    digitalWrite(trig_pin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(trig_pin, LOW);
}

int Sonar_HC_SR04::measure_distance() {
    send_pulse(this->trig_pin);
    return (pulseIn(echo_pin, HIGH) / 2 * 0.0343);
}