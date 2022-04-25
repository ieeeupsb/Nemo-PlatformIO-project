#include "nemo_motion.h"

#include "../line/line.h"
#include "../setup.h"
#include "communication/comm.h"
#include <motor.h>

#define WALK_CONST 3.43
#define ENCODER_ERROR 0
#define STABLE_STATE 0
#define CORRECT_TO_RIGHT_STATE 1
#define CORRECT_TO_LEFT_STATE 2

Motor left_motor;
Motor right_motor;

void correct_trajectory_line();

void motors_setup() {
    ESP32Encoder::useInternalWeakPullResistors = UP;
    left_motor.setup(DC_MOTOR_1L, DC_MOTOR_2L, ENABLE_L, LEFT_MOTOR_CHANNEL,
                     ENC1_L, ENC2_L);
    right_motor.setup(DC_MOTOR_1R, DC_MOTOR_2R, ENABLE_R, RIGHT_MOTOR_CHANNEL,
                      ENC1_R, ENC2_R);
}

void walk_line(int millimeters, int direction, int turn) {
    int ticks = (int32_t)(3.5 * float(millimeters));

    left_motor.encoder.setCount(0);
    right_motor.encoder.setCount(0);

    bool stop = false;
    do {
        correct_trajectory_line();
        char auxs[50];
        sprintf(auxs, "Left encoder: %d \n",
                (int32_t)left_motor.encoder.getCount());
        debug_message(auxs);
        sprintf(auxs, "Right encoder: %d \n",
                (int32_t)right_motor.encoder.getCount());
        debug_message(auxs);
        line_case_debug();
        stop = (turn == LINE_CASE_FAST) ||
               ((int32_t)left_motor.encoder.getCount() > ticks);
    } while (!stop);
    left_motor.stop();
    right_motor.stop();
}

void correct_trajectory() {
    float left_speed = fabs(left_motor.get_speed());
    float right_speed = fabs(right_motor.get_speed());

    if (left_speed < right_speed) {
        if (left_speed > MIN_SPEED) {
            left_motor.refresh(-1);
            return;
        }
        right_motor.refresh(1);
    }
    if (right_speed > left_speed) {
        if (right_speed > MIN_SPEED) {
            right_motor.refresh(-1);
            return;
        }
        left_motor.refresh(1);
        return;
    }
}

void correct_trajectory_line() {
    int _case = LINE_CASE_FAST;
    if (_case == LINE) {
        correct_trajectory;
        return;
    }

    float left_speed = fabs(left_motor.get_speed());
    float right_speed = fabs(right_motor.get_speed());

    switch (_case) {
    case CORRECT_TO_RIGHT:
        if (left_speed > MIN_SPEED) {
            left_motor.refresh(-1);
            return;
        }
        right_motor.refresh(1);
        break;
    case CORRECT_TO_LEFT:
        if (right_speed > MIN_SPEED) {
            right_motor.refresh(-1);
            return;
        }
        left_motor.refresh(1);
        break;
    default:
        debug_message("Error");
        break;
    }
    if (left_speed < right_speed) {
        if (left_speed > MIN_SPEED) {
            left_motor.refresh(-1);
            return;
        }
        right_motor.refresh(1);
    }
    if (right_speed > left_speed) {
        return;
    }
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
