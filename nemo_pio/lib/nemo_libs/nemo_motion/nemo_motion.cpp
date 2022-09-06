#include "nemo_motion.h"

#define LEFT_MOTOR_CHANNEL 0
#define RIGHT_MOTOR_CHANNEL 1

#define MASTER_MOTOR left_motor

void motion::setup() {
    ESP32Encoder::useInternalWeakPullResistors = UP;
    left_motor.setup(DC_MOTOR_1L, DC_MOTOR_2L, ENABLE_L, LEFT_MOTOR_CHANNEL,
                     ENC1_L, ENC2_L);
    right_motor.setup(DC_MOTOR_1R, DC_MOTOR_2R, ENABLE_R, RIGHT_MOTOR_CHANNEL,
                      ENC1_R, ENC2_R);
}

// TODO: test this function
void motion::refresh() {
    if (max_ticks == MASTER_MOTOR.encoder.getCount())
        stop();
    linear_speed = MASTER_MOTOR.get_speed_ms();
}
// FIXME: pwm is at 150
// TODO: test this function
void motion::walk(motor_direction_t direction) {
    // TODO: Change this in the future to set with default speed_ms;
    left_motor.set_direction(direction);
    left_motor.set_pwm(150);
    right_motor.set_direction(direction);
    right_motor.set_pwm(150);
}

void motion::walk(motor_direction_t direction, unsigned speed_ms) {
}

// TODO: test this function
void motion::set_max_distance(unsigned distance_mm) {
    max_ticks = WALK_CONST * distance_mm;
}

// TODO use set_dir_pwm
void motion::simple_walk(int pwm_left, int pwm_right) {
    // left_motor._pwmVal = pwm_left;
    // right_motor._pwmVal = pwm_right;
}

void motion::stop() {
    left_motor.stop();
    right_motor.stop();
}