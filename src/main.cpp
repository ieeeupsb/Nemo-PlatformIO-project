#include <motor.h>
#include <sonar.h>
#include <comm.h>
#include <line.h>
#include <comm.h>
#include <eletromagnet.h>

#include "./factory_lite/factory_lite.h"

void nemo_setup() {
  motors_setup();
  sonar_setup();
  line_setup();
  wifi_setup();
  eletromagnet_setup();
}

void setup() {
  factory_lite();
}

void loop(){

}