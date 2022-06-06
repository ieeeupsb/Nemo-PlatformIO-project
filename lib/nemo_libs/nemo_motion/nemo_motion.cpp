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

void motion::refresh() {
    if (max_ticks == MASTER_MOTOR.encoder.getCount())
        stop();
    linear_speed = MASTER_MOTOR.current_speed();
}

void motion::stop() {
    left_motor.stop();
    right_motor.stop();
}