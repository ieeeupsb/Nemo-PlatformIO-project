#include "nemo_motion.h"

#define ENCODER_ERROR 0
#define STABLE_STATE 0
#define CORRECT_TO_RIGHT_STATE 1
#define CORRECT_TO_LEFT_STATE 2

void correct_trajectory_line_1();
void correct_trajectory_line();
float Kp = 20, Ki = 0;

int last_time_walk = 0;
#define WALK_REFRESH_RATE 10

Motor left_motor;
Motor right_motor;

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
    int _case;

    left_motor.encoder.setCount(0);
    right_motor.encoder.setCount(0);

    // left_motor.set_speed(direction, left_motor.speed);
    // left_motor.set_speed(direction, right_motor.speed);
    // right_motor.set_speed(direction, NEMO_SPEED);
    // left_motor.set_speed(direction, NEMO_SPEED);

    while (turn != LINE_CASE_FAST) {
        switch (direction) {
        case FORWARD:
            do {
                // if (millis() - last_time_walk > WALK_REFRESH_RATE) {
                //     last_time_walk = millis();
                //     right_motor.speed = right_total / count;
                //     left_motor.speed = left_total / count;
                //     count = 0;
                //     right_total = 0;
                //     left_total = 0;
                // } else {
                //     count++;
                //     right_total += right_motor.get_speed();
                //     left_total += left_motor.get_speed();
                //     break;
                // }
                line_case_debug();
                pid_control(direction);
                // if (right_motor.get_speed() == 0) {
                //     right_motor.set_speed(direction, NEMO_PWM);
                // }
                // if (left_motor.get_speed() == 0) {
                //     left_motor.set_speed(direction, NEMO_PWM);
                // }
                _case = LINE_CASE_FAST;
                stop = ((turn == _case) ||
                        ((int32_t)left_motor.encoder.getCount() > ticks) ||
                        ((int32_t)right_motor.encoder.getCount() > ticks));
            } while (!stop);
            break;

        case BACKWARDS:
            do {
                line_case_debug();
                pid_control(direction);
                if (right_motor.get_speed() == 0) {
                    right_motor.set_speed(direction, NEMO_PWM);
                }
                if (left_motor.get_speed() == 0) {
                    left_motor.set_speed(direction, NEMO_PWM);
                }
                stop = ((turn == LINE_CASE_FAST) ||
                        (-(int32_t)left_motor.encoder.getCount() > ticks) ||
                        (-(int32_t)right_motor.encoder.getCount() > ticks));
            } while (!stop);
            break;
        }
    }
    left_motor.stop();
    right_motor.stop();
    line_case_debug();
    // debug_message("Walking a bit");
    // walk(62, FORWARD);
    return;
}

void walk(int millimeters, int direction) {
    int ticks = (int32_t)((float)(millimeters)*WALK_CONST);

    left_motor.encoder.setCount(0);
    right_motor.encoder.setCount(0);

    left_motor.set_speed(direction, NEMO_PWM);
    right_motor.set_speed(direction, NEMO_PWM);

    bool stop = false;

    switch (direction) {
    case FORWARD:
        do {
            stop = ((int32_t)left_motor.encoder.getCount() >= ticks);
            // line_case_debug();
            correct_trajectory();
        } while (!stop);
        break;
    case BACKWARDS:
        do {
            stop = (-(int32_t)left_motor.encoder.getCount() >= ticks);
            // line_case_debug();
            correct_trajectory();
        } while (!stop);
        break;
    }
    left_motor.stop();
    right_motor.stop();
}
#define KP_CT 1
void correct_trajectory() {
    float left_speed = fabs(left_motor.get_speed());
    float right_speed = fabs(right_motor.get_speed());

    if (left_speed > right_speed) {
        if (left_speed > MIN_SPEED) {
            left_motor.refresh(-KP_CT);
            return;
        }
        right_motor.refresh(KP_CT);
        return;
    }
    if (right_speed > left_speed) {
        if (right_speed > MIN_SPEED) {
            right_motor.refresh(-KP_CT);
            return;
        }
        left_motor.refresh(KP_CT);
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
        left_motor.set_speed(FORWARD, left_motor.speed);
        right_motor.set_speed(BACKWARDS, right_motor.speed);

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

int rotate_line(int degrees, int direction) {

    left_motor.encoder.setCount(0);
    right_motor.encoder.setCount(0);
    int32_t ticks;

    switch (direction) {
    case CLOCKWISE:
        ticks = (int32_t)((ROTATION_CONST)*degrees);
        left_motor.set_speed(FORWARD, left_motor.speed);
        right_motor.set_speed(BACKWARDS, right_motor.speed);

        while ((-right_motor.encoder.getCount() < ticks / 2) ||
               (LINE_CASE_FAST != LINE)) {
        }
        break;
        // while ((LINE_CASE_FAST != LINE) ||
        //        ((int32_t)left_motor.encoder.getCount() < ticks / 2)) {
        //     DEBUG_SPEED;
        // }

        // break;
    case ANTI_CLOCKWISE:
        ticks = (int32_t)(ROTATION_CONST * degrees);
        left_motor.set_speed(BACKWARDS, left_motor.speed);
        right_motor.set_speed(FORWARD, right_motor.speed);

        while (-left_motor.encoder.getCount() < (ticks / 2) ||
               !(LINE_CASE_FAST == LINE)) {
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

void pid_control(int direction) {
    // static float I = 0;
    // float P = 0;
    // float Kp = 25, Ki = 0;

    // int _case = LINE_CASE_FAST;

    // switch (_case) {
    // case (LINE):
    //     P = 0.0;
    //     break;
    // case (CORRECT_TO_LEFT):
    //     P = 1.0;
    //     break;
    // case (CORRECT_TO_RIGHT):
    //     P = -1.0;
    //     break;
    // case (SHARP_LEFT):
    //     P = 2.0;
    //     break;
    // case (SHARP_RIGHT):
    //     P = -2.0;
    //     break;
    // }

    // I += P;

    // int pidValue = (int)((P * Kp) + (I * Ki));

    // right_motor.set_pwm(right_motor.pwm_average + pidValue);
    // left_motor.set_pwm(left_motor.pwm_average - pidValue);
}

void andamento(int millimeters, int direction) {
    int ticks = (int32_t)((float)(millimeters)*WALK_CONST);

    left_motor.encoder.setCount(0);
    right_motor.encoder.setCount(0);

    while (fabs((int32_t)left_motor.encoder.getCount()) < ticks) {
        delay(30);
        line_case_debug();
        pid_speed(direction);
    }
}

void andamento_linha(int direction, int turn) {
    int _case = 0;

    while (1) {

        delay(30);
        pid(direction);
        line_case_debug();
        _case = LINE_CASE_FAST;
        if (_case == turn) {
            delay(5);
            if (LINE_CASE_FAST == turn) {
                break;
            }
        }
    }
    while (1) {
        delay(30);
        pid_speed(direction);
        line_case_debug();
        _case = LINE_CASE_FAST;
        if (_case == turn) {
            delay(5);
            if (LINE_CASE_FAST == turn) {
                break;
            }
        }
    }
}

void pid(int direction) {

    static float I = 0;
    float P = 0;
    float pidValue = 0;
    int right_speed, left_speed;

    right_speed = fabs(right_motor.get_speed());
    left_speed = fabs(left_motor.get_speed());

    int _case = LINE_CASE_FAST;

    switch (_case) {
    case (LINE):
        P = 0.0;
        break;
    case (CORRECT_TO_LEFT):
        P = 1.0;
        break;
    case (CORRECT_TO_RIGHT):
        P = -1.0;
        break;
    case (SHARP_LEFT):
        P = 2.0;
        break;
    case (SHARP_RIGHT):
        P = -2.0;
        break;
    case (RIGHT_CURVE):
        P = 1.0;
        break;
    case (LEFT_CURVE):
        P = -1.0;
        break;
    }

    I += P;

    // certifica-se de que anda
    // if ((right_speed <= 0.001) || (left_speed <= 0.001)) {
    //     if (!right_speed > 0.001) {
    //         right_motor.refresh(1);
    //     }

    //     if (left_speed > 0.001) {
    //         left_motor.refresh(1);
    //     }
    //     return;
    // }

    pidValue = P * Kp + I * Ki;

    // speed value in PWM
    right_speed = NEMO_PWM + pidValue;
    left_speed = NEMO_PWM - pidValue;

    right_motor.set_speed(direction, right_speed);
    left_motor.set_speed(direction, left_speed);
}

void pid_speed(int direction) {
    int P;
    int pidValue = 0;

    float left_speed = fabs(left_motor.get_speed());
    float right_speed = fabs(right_motor.get_speed());

    // certifica-se de que anda
    // if ((right_speed <= 0.001) || (left_speed <= 0.001)) {
    //     if (!right_speed > 0.001) {
    //         right_motor.refresh(1);
    //     }

    //     if (left_speed > 0.001) {
    //         left_motor.refresh(1);
    //     }
    //     return;
    // }

    if (left_speed > right_speed) {
        P = 1;
    }
    if (right_speed > left_speed) {
        P = -1;
    }

    pidValue = Kp * P;

    right_speed = NEMO_PWM + pidValue;
    left_speed = NEMO_PWM - pidValue;

    right_motor.set_speed(direction, right_speed);
    left_motor.set_speed(direction, left_speed);
    return;
}