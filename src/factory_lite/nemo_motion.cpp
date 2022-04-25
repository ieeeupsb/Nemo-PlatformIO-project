#include "nemo_motion.h"

#include "../line/line.h"
#include "../motor/motor.h"
#include "communication/comm.h"
#include "factory_lite.h"
#include "setup.h"

Motor left_motor;
Motor right_motor;

void motors_setup() {
    ESP32Encoder::useInternalWeakPullResistors = UP;
    left_motor.setup(DC_MOTOR_1L, DC_MOTOR_2L, ENABLE_L, LEFT_MOTOR_CHANNEL,
                     ENC1_L, ENC2_L);
    right_motor.setup(DC_MOTOR_1R, DC_MOTOR_2R, ENABLE_R, RIGHT_MOTOR_CHANNEL,
                      ENC1_R, ENC2_R);
}

void walk(int millimeters, int direction, int turn) {
    int left_speed = NEMO_SPEED;
    int right_speed = NEMO_SPEED;
    left_motor.encoder.setCount(0);
    right_motor.encoder.setCount(0);

    int ticks = (int32_t)(3.43 * float(millimeters));
    left_motor.set_speed(direction, left_speed);
    right_motor.set_speed(direction, right_speed);

    while ((int32_t)left_motor.encoder.getCount() == ticks) {
        if (LINE_CASE_FAST == turn)
            break;
        switch (LINE_CASE_FAST) {
        case CORRECT_TO_LEFT:
            right_motor.set_speed(direction, right_speed--);
            break;
        case CORRECT_TO_RIGHT:
            right_motor.set_speed(direction, left_speed--);
            break;
        case LINE:
            left_motor.set_speed(direction, NEMO_SPEED);
            right_motor.set_speed(direction, NEMO_SPEED);
            right_speed = NEMO_SPEED;
            left_speed = NEMO_SPEED;
            break;
        }
    }
    left_motor.stop();
    right_motor.stop();
}

void rotate(int degrees, int direction, int speed) {

    int left_speed = speed;
    int right_speed = speed;
    left_motor.encoder.setCount(0);
    right_motor.encoder.setCount(0);
    int32_t ticks;

    switch (direction) {
    case CLOCKWISE:
        ticks = (int32_t)((-2200 / 360.0) * degrees);
        left_motor.set_speed(FORWARD, left_speed);
        right_motor.set_speed(BACKWARDS, right_speed);

        while (right_motor.encoder.getCount() > -ticks) {
        }
        break;
    case ANTI_CLOCKWISE:
        ticks = (int32_t)((-2200 / 360.0) * degrees);
        left_motor.set_speed(BACKWARDS, left_speed);
        right_motor.set_speed(FORWARD, right_speed);

        while (left_motor.encoder.getCount() > -ticks) {
        }
        break;
    default:
        debug_message("invalid direction");
        break;
    }
    left_motor.stop();
    right_motor.stop();
}
