#include "motion.h"

void Motion::setup() {
    left_wheel.setup(DC_MOTOR_1L, DC_MOTOR_2L,
                     ENABLE_L, 0, ENC1_L,
                     ENC2_L);
    right_wheel.setup(DC_MOTOR_1R, DC_MOTOR_2R,
                      ENABLE_R, 1, ENC1_R,
                      ENC2_R);
}

void Motion::set_motion_test() {
    setup();
    left_wheel.set_rotation_dir(CLOCKWISE);
    right_wheel.set_rotation_dir(CLOCKWISE);
}

// FIXME tirei os motores a pararem por questões de teste.
void Motion::test_motors() {

    set_motion_test();
    left_wheel.set_max_speed();
    right_wheel.set_max_speed();
    delay(200);
    // stop();
}

void Motion::stop() {
    left_wheel.stop();
    right_wheel.stop();
}

void Motion::test_encoders() {
    set_motion_test();

    left_wheel.set_max_distance(200);
    right_wheel.set_max_distance(200);

    left_wheel.set_max_speed();
    while (!left_wheel.is_max_distance()) {
    }
    stop();

    right_wheel.set_max_speed();
    while (!right_wheel.is_max_distance()) {
    }
    stop();
}

// void Motion::test_wheels() {
//     test_motors();
//     delay(500);
//     test_enconders();
// }