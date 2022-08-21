#include "mode_main.h"

#include "ESP32_pinout.h"
#include "motor.h"
#include "nemo_motion.h"
motion nemo_motion_g;

void setup() {
    nemo_motion_g.setup();
    nemo_motion_g.set_max_distance(300);
    nemo_motion_g.walk(FORWARD);
}

void loop() {
    nemo_motion_g.refresh();
}
