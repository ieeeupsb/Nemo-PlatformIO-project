// ssh ieeeupsb@192.168.0.162 ethernet
// 192.168.0.128 wifi
// pass 1234

#include "Arduino.h"
#include "PID_v1.h"
#include "RPi_Pico_TimerInterrupt.h"
#include "micro_controller_unit.h"
#include "motion_controller.h"

#define TIMER0_INTERVAL_MS 50
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

pose_t current_pose;

pose_t pose_estimator(pose_t current_pose, float enlapsed_time, float left_wheel_speed, float right_wheel_speed, float wheel_base) {

    if (!left_wheel_speed && !right_wheel_speed) {
        return current_pose;
    }

    float linear_speed = (left_wheel_speed + right_wheel_speed) / 2;
    float angular_speed = (right_wheel_speed - left_wheel_speed) / wheel_base;

    // Serial.print("linear_speed:");
    // Serial.println(linear_speed);

    pose_t estimated_pose;

    estimated_pose.x_pos = current_pose.x_pos + enlapsed_time * linear_speed * cos(current_pose.angle_pos);
    estimated_pose.y_pos = current_pose.y_pos + enlapsed_time * linear_speed * sin(current_pose.angle_pos);
    estimated_pose.angle_pos = current_pose.angle_pos + enlapsed_time * angular_speed;

    // Serial.print("estimated_pose.x_pos:");
    // Serial.println(estimated_pose.x_pos);

    return estimated_pose;
}

bool TimerHandler0(struct repeating_timer *t) {

    float left_speed = (double)abs(encoder_counter_left) / (double)TIMER0_INTERVAL_MS;
    float right_speed = (double)abs(encoder_counter_right) / (double)TIMER0_INTERVAL_MS;

    rpm_last_read_left_pid_input = left_speed * 100;
    double left_linear_speed_m_per_s = left_speed * 3.1415 * 0.068 / 0.36;
    rpm_last_read_right_pid_input = right_speed * 100;
    double right_linear_speed_m_per_s = right_speed * 3.1415 * 0.068 / 0.36;

    encoder_counter_left = 0;
    encoder_counter_right = 0;

    leftWheelPID.Compute();
    rightWheelPID.Compute();

    left_driver_controller.setPwm(left_pwm_output);
    right_driver_controller.setPwm(right_pwm_output);

    current_pose = pose_estimator(current_pose, (double)TIMER0_INTERVAL_MS / 1000.00, left_linear_speed_m_per_s, right_linear_speed_m_per_s, 159e-3);

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

    ITimer0.attachInterruptInterval(TIMER0_INTERVAL_MS * 1000, TimerHandler0);

    // turn the PID on
    leftWheelPID.SetMode(AUTOMATIC);
    rightWheelPID.SetMode(AUTOMATIC);

    left_driver_controller.setDirection(motor_rotation_dir_t::ANTI_CLOCKWISE);
    right_driver_controller.setDirection(motor_rotation_dir_t::CLOCKWISE);

    target_speed_left = 30;
    target_speed_right = 30;
}

#define TIME_INTERVAL 1000

int speed_control_state = 0;
int start_stop_state = 0;

String incomingString;

void loop() {

    if (Serial.available() > 0) {
        // read the incoming string:
        incomingString = Serial.readString();

        // prints the received data
        Serial.print("I received '");
        Serial.print(incomingString);
        Serial.println("' from serial \n");
    }

    // Serial.print("rpm left: ");
    // Serial.println(rpm_last_read_left_pid_input);
    // Serial.print("rpm right: ");
    // Serial.println(rpm_last_read_right_pid_input);
    // Serial.println("rpm right: ");
    // Serial.print("x:");
    // Serial.println(current_pose.x_pos);

    // if (current_pose.x_pos == 1) {
    //     left_driver_controller.stopMotor();
    //     right_driver_controller.stopMotor();
    // }

    switch (start_stop_state) {
    case 0:

        target_speed_left = 0;
        target_speed_right = 0; // compare the input with "stop"

        left_driver_controller.stopMotor();
        right_driver_controller.stopMotor();

        incomingString.toLowerCase(); // convert the input to lowercase // read the data as string
        if (incomingString == "start\n" || incomingString == "start") {
            Serial.println("Robot going to start state");

            start_stop_state = 0;
        }
        break;

    case 1:

        left_driver_controller.setDirection(motor_rotation_dir_t::ANTI_CLOCKWISE);
        right_driver_controller.setDirection(motor_rotation_dir_t::CLOCKWISE);

        target_speed_left = 30;
        target_speed_right = 30;

        incomingString.toLowerCase(); // convert the input to lowercase // read the data as string
        if (incomingString == "stop\n" || incomingString == "stop") {

            Serial.println("Robot going to stop state");

            start_stop_state = 1;
        }
        break;
    }
}
