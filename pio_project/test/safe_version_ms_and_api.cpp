#include "Arduino.h"
#include "RPi_Pico_TimerInterrupt.h"

#define UPDATE_COUNT_US 50
#define TIMER0_INTERVAL_MS 250

#include "mcu_api.h"
#include "motion_controller.h"

// x:10.5;y:43.34;v:66.6;w:3.14;
RPI_PICO_Timer ITimer0(0);
RPI_PICO_Timer ITimer1(1);

McuAPI api(BAUD_RATE);
MotionController &robot = MotionController::getInstance();

double current_x = 0;
double parameter_1 = 0;
double parameter_2 = 0;
double parameter_3 = 0;

bool api_read_serial = false;
bool last_command_done = false;

bool TimerHandler0(struct repeating_timer *t) {

    api.timerHandler(0, 0);
    // Serial.println("TimerHandler");

    return true;
}

void updateLeftCount() {
    robot.updateLeftCount();
}

void updateRightCount() {
    robot.updateRightCount();
}

void wait_for_first_command() {
    int counter = 1;
    api.createPositionCommand(1, 3, 10);
    Serial.println("Waiting for the first command");
    while (0 == api.commandListSize()) {
        if (3 < counter) {
            counter = 0;
            Serial.print("\r                       \r");
        } else {

            Serial.print(".");
        }
        counter++;

        delay(500);
        api.parseInputAndCreateCommand();
    }
}

void setup() {

    Serial.begin(9600);

    // ITimer0.attachInterruptInterval(TIMER0_INTERVAL_MS * 1000, TimerHandler0);
    if (api_read_serial) {
        ITimer0.attachInterruptInterval(50 * 1000, TimerHandler0);
    }
    // ITimer1.attachInterruptInterval(UPDATE_COUNT_US, TimerHandler1);
    attachInterrupt(digitalPinToInterrupt(ENC_C1_PIN_L), updateLeftCount, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENC_C1_PIN_R), updateRightCount, CHANGE);

    // robot.test_motors();
    // motion_controller.test_encoders();
}

// trajectory_t robot_trajectory;
wheels_speed_t generated_wheels_speed;
wheels_speed_t wheels_current_speed;

double left_wheel_speed = 0.25; // teoricamente m/s
double right_wheel_speed = 0.25;

void loop() {
    delay(300);
    wheels_current_speed = robot.wheel_speed_calculator();

    api.parseInputAndCreateCommand();
    if (api.commandListSize()) {
        Serial.println("New commad");

        pico_command_t current_command = api.getNextCommand();

        current_x = current_command.x;
        parameter_1 = current_command.y;
        parameter_2 = current_command.v;
        parameter_3 = current_command.w;

    } else {
        current_x = 0;
        parameter_1 = 0;
        parameter_2 = 0;
        parameter_3 = 0;
    }

    generated_wheels_speed = robot.velocities_generator(parameter_2, parameter_3);

    left_wheel_speed = generated_wheels_speed.left_wheel_speed;
    right_wheel_speed = generated_wheels_speed.right_wheel_speed;

    robot.motor_controller(left_wheel_speed, right_wheel_speed);
    api.loopErrorDetection();
}