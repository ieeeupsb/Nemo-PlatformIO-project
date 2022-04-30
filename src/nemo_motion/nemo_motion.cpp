#include "nemo_motion.h"

#define ENCODER_ERROR 0
#define STABLE_STATE 0
#define CORRECT_TO_RIGHT_STATE 1
#define CORRECT_TO_LEFT_STATE 2

Motor left_motor;
Motor right_motor;

void correct_trajectory_line_1();
void correct_trajectory_line();

void motors_setup() {
    ESP32Encoder::useInternalWeakPullResistors = UP;
    left_motor.setup(DC_MOTOR_1L, DC_MOTOR_2L, ENABLE_L, LEFT_MOTOR_CHANNEL,
                     ENC1_L, ENC2_L);
    right_motor.setup(DC_MOTOR_1R, DC_MOTOR_2R, ENABLE_R, RIGHT_MOTOR_CHANNEL,
                      ENC1_R, ENC2_R);
}

void walk_line(int millimeters, int direction, int turn) {
    int ticks = (int32_t)(3.7 * float(millimeters));
    bool stop = false;

    left_motor.encoder.setCount(0);
    right_motor.encoder.setCount(0);

    left_motor.set_speed(direction, NEMO_SPEED);
    right_motor.set_speed(direction, NEMO_SPEED);

    switch (direction) {
    case FORWARD:
        do {
            line_case_debug();
            pid_control(direction);
            stop = (turn == LINE_CASE_FAST) ||
                   ((int32_t)left_motor.encoder.getCount() > ticks) ||
                   ((int32_t)right_motor.encoder.getCount() > ticks);
        } while (!stop);
        break;

    case BACKWARDS:
        do {
            DEBUG_SPEED;
            pid_control(direction);
            stop = (turn == LINE_CASE_FAST) ||
                   (-(int32_t)left_motor.encoder.getCount() > ticks) ||
                   (-(int32_t)right_motor.encoder.getCount() > ticks);
        } while (!stop);
        break;
    }

    left_motor.stop();
    right_motor.stop();

    walk(65, FORWARD);
}

void walk_sonar(int millimeters, int direction) {
    int ticks = (int32_t)(3.7 * float(millimeters));
    bool stop = false;

    left_motor.encoder.setCount(0);
    right_motor.encoder.setCount(0);

    left_motor.set_speed(direction, NEMO_SPEED);
    right_motor.set_speed(direction, NEMO_SPEED);

    unsigned long last = 0;

    // while (left_motor.get_speed() < 2 || right_motor.get_speed() < 2) {
    //     if (millis() - last > 1000) {
    //         left_motor.refresh(1);
    //         right_motor.refresh(1);
    //         last = millis();
    //         DEBUG_SPEED;
    //     }
    //     correct_trajectory();
    //     }

    switch (direction) {
    case FORWARD:
        do {
            DEBUG_SPEED;
            pid_control(direction);
            stop = ((distance(SONAR_TRIG, SONAR_ECHO)) <= 5) ||
                   ((int32_t)left_motor.encoder.getCount() > ticks);
        } while (!stop);
        break;

    case BACKWARDS:
        do {
            DEBUG_SPEED;
            pid_control(direction);
            stop = ((distance(SONAR_TRIG, SONAR_ECHO)) <= 5) ||
                   (-(int32_t)left_motor.encoder.getCount() > ticks);
        } while (!stop);
        break;
    }

    left_motor.stop();
    right_motor.stop();
}

void walk(int millimeters, int direction) {
    int ticks = (int32_t)((float)(millimeters)*WALK_CONST);

    left_motor.encoder.setCount(0);
    right_motor.encoder.setCount(0);

    left_motor.set_speed(direction, NEMO_SPEED);
    right_motor.set_speed(direction, NEMO_SPEED);
    bool stop = false;

    switch (direction) {
    case FORWARD:
        do {
            stop = ((int32_t)left_motor.encoder.getCount() >= ticks);
            debug_encoder(left_motor);
            correct_trajectory();
            DEBUG_SPEED;
        } while (!stop);
        break;
    case BACKWARDS:
        do {
            stop = (-(int32_t)left_motor.encoder.getCount() >= ticks);
            correct_trajectory();
        } while (!stop);
        break;
    }
    left_motor.stop();
    right_motor.stop();
}

void correct_trajectory() {
    float left_speed = fabs(left_motor.get_speed());
    float right_speed = fabs(right_motor.get_speed());

    // char auxs[128];
    // sprintf(auxs, "left speed; %f  | right speed: %f", left_speed,
    // right_speed); debug_message(auxs);
    if (left_speed > right_speed) {
        if (left_speed > MIN_SPEED) {
            left_motor.refresh(-1);
            return;
        }
        right_motor.refresh(1);
        return;
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

void correct_trajectory_line_1() {
    float left_speed = fabs(left_motor.get_speed());
    float right_speed = fabs(right_motor.get_speed());
    int _case = LINE_CASE_FAST;

    if (_case == LINE) {
        correct_trajectory();
        return;
    }

    // char auxs[128];
    // sprintf(auxs, "left speed; %f  | right speed: %f", left_speed,
    // right_speed); debug_message(auxs);
    if (_case == CORRECT_TO_LEFT) {
        if (left_speed > MIN_SPEED) {
            left_motor.refresh(-1);
            return;
        }
        if ((right_speed < MAX_SPEED) && (right_speed > MIN_SPEED)) {
            right_motor.refresh(1);
            return;
        }
    }
    if (_case == CORRECT_TO_RIGHT) {
        if (right_speed > MIN_SPEED) {
            right_motor.refresh(-1);
            return;
        }
        if (left_speed < MAX_SPEED) {
            left_motor.refresh(1);
            return;
        }
    }
}

int last_time_line = 0;
void correct_trajectory_line() {

    int _case = LINE_CASE_FAST;
    if (_case == LINE) {
        correct_trajectory();
        return;
    }

    float left_speed = fabs(left_motor.get_speed());
    float right_speed = fabs(right_motor.get_speed());

    switch (_case) {
    case CORRECT_TO_LEFT:
        debug_message("correcting to right");
        if (left_speed > MAX_SPEED) {
            left_motor.refresh(-1);
            return;
        }

        right_motor.refresh(1);

        break;
    case CORRECT_TO_RIGHT:
        debug_message("correcting to left");
        if (right_speed > MAX_SPEED) {
            right_motor.refresh(-1);
            return;
        }

        if (millis() - last_time_line > 7) {
            last_time_line = millis();
            if (left_speed < MIN_SPEED)
                left_motor.refresh(1);
            return;
        } else
            return;

        break;
    default:
        debug_message("Error");
        break;
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
        ticks = (int32_t)(ROTATION_CONST * degrees);
        left_motor.set_speed(FORWARD, left_speed);
        right_motor.set_speed(BACKWARDS, right_speed);

        while (-right_motor.encoder.getCount() < ticks) {
            DEBUG_SPEED;
        }
        break;
    case ANTI_CLOCKWISE:
        ticks = (int32_t)(ROTATION_CONST * degrees);
        left_motor.set_speed(BACKWARDS, left_speed);
        right_motor.set_speed(FORWARD, right_speed);

        while (-left_motor.encoder.getCount() < ticks) {
            DEBUG_SPEED;
        }
        break;
    default:
        debug_message("invalid direction");
        break;
    }
    left_motor.stop();
    right_motor.stop();
}

int rotate_line(int degrees, int direction, int speed) {

    int left_speed = speed;
    int right_speed = speed;
    left_motor.encoder.setCount(0);
    right_motor.encoder.setCount(0);
    int32_t ticks;

    switch (direction) {
    case CLOCKWISE:
        ticks = (int32_t)((ROTATION_CONST)*degrees);
        left_motor.set_speed(FORWARD, left_speed);
        right_motor.set_speed(BACKWARDS, right_speed);

        while ((-right_motor.encoder.getCount() < ticks / 2) ||
               (LINE_CASE_FAST != LINE)) {
            DEBUG_SPEED;
        }
        break;
        // while ((LINE_CASE_FAST != LINE) ||
        //        ((int32_t)left_motor.encoder.getCount() < ticks / 2)) {
        //     DEBUG_SPEED;
        // }

        // break;
    case ANTI_CLOCKWISE:
        ticks = (int32_t)(ROTATION_CONST * degrees);
        left_motor.set_speed(BACKWARDS, left_speed);
        right_motor.set_speed(FORWARD, right_speed);

        while (-left_motor.encoder.getCount() < (ticks / 2) ||
               !(LINE_CASE_FAST == LINE)) {
            DEBUG_SPEED;
        }
        // while (right.encoder.getCount() < (ticks / 2) ||
        //        !(LINE_CASE_FAST == LINE)) {
        //     DEBUG_SPEED;
        // }
        break;
    default:
        debug_message("invalid direction");
        break;
    }

    left_motor.stop();
    right_motor.stop();

    return 0;
}

int P = 0, I = 0;
void pid_control(int direction) {

    int Kp = 20, Ki = 0;
    int pidValue = 0;
    int right_speed, left_speed;

    int _case = LINE_CASE_FAST;

    switch (_case) {
    case (LINE):
        P = 0;
        break;
    case (CORRECT_TO_LEFT):
        P = 1;
        break;
    case (CORRECT_TO_RIGHT):
        P = -1;
        break;
    case (SHARP_LEFT):
        P = 2;
        break;
    case (SHARP_RIGHT):
        P = -2;
        break;
    }

    I += P;

    pidValue = (P * Kp) + (I * Ki);

    right_speed = NEMO_SPEED + pidValue;
    left_speed = NEMO_SPEED - pidValue;

    right_motor.set_speed(direction, right_speed);
    left_motor.set_speed(direction, left_speed);
}