// ssh ieeeupsb@192.168.0.162
// pass 1234

#include "Arduino.h"
#include "PID_v1.h"
#include "RPi_Pico_TimerInterrupt.h"
#include "micro_controller_unit.h"
#include "pidautotuner.h"

#define TIMER0_INTERVAL_MS 200
RPI_PICO_Timer ITimer0(0);

MicroControllerUnit &mcu = MicroControllerUnit::getInstance();

DriverController left_driver_controller(DRIVER_ENABLE_PIN_L, DRIVER_IN_A_PIN_L, DRIVER_IN_B_PIN_L);
DriverController right_driver_controller(DRIVER_ENABLE_PIN_R, DRIVER_IN_A_PIN_R, DRIVER_IN_B_PIN_R);

double target_speed_left, rpm_last_read_left_pid_input, left_pwm_output;
double target_speed_right, rpm_last_read_right_pid_input, right_pwm_output;

double Kp = 1 * 0.7, Ki = 1.4, Kd = 0;
PID leftWheelPID(&rpm_last_read_left_pid_input, &left_pwm_output, &target_speed_left, Kp, Ki, Kd, DIRECT);
PID rightWheelPID(&rpm_last_read_right_pid_input, &right_pwm_output, &target_speed_right, Kp, Ki, Kd, DIRECT);

volatile int encoder_counter_left = 0;
volatile int encoder_counter_right = 0;

bool TimerHandler0(struct repeating_timer *t) {

    float right_speed = (float)encoder_counter_right / (float)TIMER0_INTERVAL_MS;
    float left_speed = (float)encoder_counter_left / (float)TIMER0_INTERVAL_MS;

    rpm_last_read_right_pid_input = right_speed * 100;
    rpm_last_read_left_pid_input = left_speed * 100;

    encoder_counter_left = 0;
    encoder_counter_right = 0;

    leftWheelPID.Compute();
    rightWheelPID.Compute();

    left_driver_controller.setPwm(left_pwm_output);
    right_driver_controller.setPwm(right_pwm_output);

    return true;
}

void updateLeftCount() {
    int a_state = digitalRead(ENC_C1_PIN_L);
    int b_state = digitalRead(ENC_C2_PIN_L);

    if (a_state == b_state) {
        encoder_counter_left++;
    } else {
        encoder_counter_left--;
    }
}

void updateRightCount() {
    int a_state = digitalRead(ENC_C1_PIN_R);
    int b_state = digitalRead(ENC_C2_PIN_R);

    if (a_state == b_state) {
        encoder_counter_right++;
    } else {
        encoder_counter_right--;
    }
}

void setup() {
    Serial.begin(9600);

    pinMode(ENC_C1_PIN_R, rpm_last_read_left_pid_input);
    pinMode(ENC_C2_PIN_R, rpm_last_read_left_pid_input);

    attachInterrupt(digitalPinToInterrupt(ENC_C1_PIN_L), updateLeftCount, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENC_C1_PIN_R), updateRightCount, CHANGE);
    // right_driver_controller.setPwm(70);
    // left_driver_controller.setDirection(motor_rotation_dir_t::ANTI_CLOCKWISE);
    right_driver_controller.setDirection(motor_rotation_dir_t::CLOCKWISE);

    ITimer0.attachInterruptInterval(TIMER0_INTERVAL_MS * 1000, TimerHandler0);
    target_speed_left = 0;
    target_speed_right = 100;

    // turn the PID on
    leftWheelPID.SetMode(AUTOMATIC);
    rightWheelPID.SetMode(AUTOMATIC);
}

#define TIME_INTERVAL 1000

int speed_control_state = 0;

void loop() {

    Serial.print("rpm left: ");
    Serial.println(rpm_last_read_left_pid_input);
    Serial.print("rpm right: ");
    Serial.println(rpm_last_read_right_pid_input);

    switch (speed_control_state) {
    case 0: // from small loop for PID

        speed_control_state = 1;
        break;
    case 1: // get target
        // gets target from User
        // sets speed_control_state to 0
        break;
    default:
        break;
    }
}