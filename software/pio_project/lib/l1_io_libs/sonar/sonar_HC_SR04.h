#pragma once

#include "ports.h"
#include "wiring_private.h"
#include <stdint.h>

class Sonar_HC_SR04 {
  private:
    uint8_t trig_pin;
    uint8_t echo_pin;

  public:
    Sonar_HC_SR04(uint8_t trig_pin, uint8_t echo_pin);
    int measure_distance();
}
