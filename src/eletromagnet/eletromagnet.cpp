#include "eletromagnet.h"

#include "../src/setup.h"
#include <Arduino.h>

void eletromagnet_setup() { pinMode(ELECTROMAGNET, OUTPUT); }
void eletromagnet_on() { digitalWrite(ELECTROMAGNET, HIGH); }
void eletromagnet_off() { digitalWrite(ELECTROMAGNET, LOW); }