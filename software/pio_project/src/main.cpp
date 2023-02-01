// // ssh ieeeupsb@192.168.0.162 ethernet
// // 192.168.0.128 wifi
// // pass 1234

// #include "Arduino.h"
// #include "motion_controller.h"

// RPI_PICO_Timer ITimer0(0);
// // RPI_PICO_Timer ITimer1(0);

// MicroControllerUnit &mcu = MicroControllerUnit::getInstance();

// bool TimerHandler0(struct repeating_timer *t) {

//     mcu.speedTimerHandler();
//     return true;
// }

// bool TimerHandler1(struct repeating_timer *t) {

//     mcu.apiTimerHandler();
//     return true;
// }

// void setup() {
//     pinMode(ENC_C1_PIN_R, rpm_last_read_left_pid_input);
//     pinMode(ENC_C2_PIN_R, rpm_last_read_left_pid_input);

//     attachInterrupt(digitalPinToInterrupt(ENC_C1_PIN_L), updateLeftCount, CHANGE);
//     attachInterrupt(digitalPinToInterrupt(ENC_C1_PIN_R), updateRightCount, CHANGE);
//     // right_driver_controller.setPwm(70);

//     ITimer0.attachInterruptInterval(TIMER0_INTERVAL_MS * 1000, TimerHandler0);

//     // turn the PID on
//     leftWheelPID.SetMode(AUTOMATIC);
//     rightWheelPID.SetMode(AUTOMATIC);

//     left_driver_controller.setDirection(motor_rotation_dir_t::ANTI_CLOCKWISE);
//     right_driver_controller.setDirection(motor_rotation_dir_t::CLOCKWISE);

//     // target_speed_left = 100;
//     // target_speed_right = 100;
//     left_driver_controller.setPwm(120);
//     right_driver_controller.setPwm(120);
// }

// #define TIME_INTERVAL 1000

// int speed_control_state = 0;

// void loop() {

//     // // Serial.print("rpm left: ");
//     // // Serial.println(rpm_last_read_left_pid_input);
//     // // Serial.print("rpm right: ");
//     // // Serial.println(rpm_last_read_right_pid_input);
//     // // Serial.println("rpm right: ");
//     // // Serial.print("x:");
//     // // Serial.println(current_pose.x_pos);

//     // // if (current_pose.x_pos == 1) {
//     // //     left_driver_controller.stopMotor();
//     // //     right_driver_controller.stopMotor();
//     // // }

//     // switch (start_stop_state) {
//     // case STOP_STATE:

//     //     target_speed_left = 0;
//     //     target_speed_right = 0; // compare the input with "stop"

//     //     left_driver_controller.stopMotor();
//     //     right_driver_controller.stopMotor();

//     //     incomingString.toLowerCase(); // convert the input to lowercase // read the data as string
//     //     if (incomingString == "start\n" || incomingString == "start") {
//     //         Serial.println("Robot going to start state");

//     //         start_stop_state = START_STATE;
//     //     }

//     //     // if (incomingString == "rotate\n" || incomingString == "rotate") {

//     //     //     Serial.println("Robot going to rotation state");

//     //     //     start_stop_state = ROTATE_STATE;
//     //     // }
//     //     break;

//     // case START_STATE:

//     //     left_driver_controller.setDirection(motor_rotation_dir_t::ANTI_CLOCKWISE);
//     //     right_driver_controller.setDirection(motor_rotation_dir_t::CLOCKWISE);

//     //     incomingString.toLowerCase(); // convert the input to lowercase // read the data as string
//     //     if (incomingString == "stop\n" || incomingString == "stop") {

//     //         Serial.println("Robot going to stop state");

//     //         start_stop_state = STOP_STATE;
//     //     }

//     //     if (v_w_input(incomingString)) {
//     //         break;
//     //     }

//     //     // if (incomingString == "rotate\n" || incomingString == "rotate") {

//     //     //     Serial.println("Robot going to rotation state");

//     //     //     start_stop_state = ROTATE_STATE;
//     //     // }
//     //     break;

//     //     // case ROTATE_STATE:

//     //     //     left_driver_controller.setDirection(motor_rotation_dir_t::CLOCKWISE);
//     //     //     right_driver_controller.setDirection(motor_rotation_dir_t::CLOCKWISE);

//     //     //     target_speed_left = 30;
//     //     //     target_speed_right = 30;

//     //     //     incomingString.toLowerCase(); // convert the input to lowercase // read the data as string
//     //     //     if (incomingString == "start\n" || incomingString == "start") {
//     //     //         Serial.println("Robot going to start state");

//     //     //         start_stop_state = START_STATE;
//     //     //     }
//     //     //     if (incomingString == "stop\n" || incomingString == "stop") {

//     //     //         Serial.println("Robot going to stop state");

//     //     //         start_stop_state = STOP_STATE;
//     //     //     }
//     //     //     break;
//     // }
// }

#include "Arduino.h"
#include "RPi_Pico_TimerInterrupt.h"
#include "mcu_api.h"

RPI_PICO_Timer ITimer0(0);

McuAPI API(9600);

bool TimerHandler0(struct repeating_timer *t) {

    API.timerHandler(0, 0);

    return true;
}

void setup() {
    ITimer0.attachInterruptInterval(TIMER0_INTERVAL_MS * 1000, TimerHandler0);
}

// x:10.5;y:43.34;v:66.6;w:3.14;

void loop() {
    delay(1000);

    API.parseInputAndCreateCommand();
}
