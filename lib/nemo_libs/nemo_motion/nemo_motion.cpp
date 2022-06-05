#include "nemo_motion.h"

#define LEFT_MOTOR_CHANNEL 0
#define RIGHT_MOTOR_CHANNEL 1

void motion::setup() {
    ESP32Encoder::useInternalWeakPullResistors = UP;
    left_motor.setup(DC_MOTOR_1L, DC_MOTOR_2L, ENABLE_L, LEFT_MOTOR_CHANNEL,
                     ENC1_L, ENC2_L);
    right_motor.setup(DC_MOTOR_1R, DC_MOTOR_2R, ENABLE_R, RIGHT_MOTOR_CHANNEL,
                      ENC1_R, ENC2_R);
}