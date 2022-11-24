#pragma once

#include "ports.h"

class Sonar_HC_SR04 {
  private:
    uint8_t trig_pin;
    uint8_t echo_pin;

  public:
    Sonar_HC_SR04nar(uint8_t trig_pin, uint8_t echo_pin);

    void set_trig_pin(uint8_t new_trig_pin);
    void set_echo_pin(uint8_t new_echo_pin);
    int measure_distance();
