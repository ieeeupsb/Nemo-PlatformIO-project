#include "communication/comm.h"
#include "eletromagnet/eletromagnet.h"
#include "line/line.h"
#include "sonar/sonar.h"

#include "motor/motor.h"

#include "factory_lite/factory_lite.h"

void nemo_setup() {
    motors_setup();
    sonar_setup();
    line_setup();
    wifi_setup();
    eletromagnet_setup();
}

void setup() { factory_lite(); }

void loop() {}