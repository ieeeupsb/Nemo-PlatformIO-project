#include "Arduino.h"
#include "RPi_Pico_TimerInterrupt.h"

#define SPEED_TIMER_INTERVAL_MS 50
#define TIMER0_INTERVAL_MS 500

#include "mcu_api.h"
#include "motion_controller.h"

// x:10.5;y:43.34;v:66.6;w:3.14;
RPI_PICO_Timer ITimer0(0);
RPI_PICO_Timer ITimer1(1);

McuAPI api(BAUD_RATE);
MotionController &motion_controller = MotionController::getInstance();

double current_x = 0;
double current_y = 0;
double current_v = 0;
double current_w = 0;

bool last_command_done = false;

bool TimerHandler0(struct repeating_timer *t) {

    api.timerHandler(0, 0);

    return true;
}

bool TimerHandler1(struct repeating_timer *t) {

    motion_controller.speedTimerHandler();

    return true;
}

void updateLeftCount() {
    motion_controller.updateLeftCount();
}

void updateRightCount() {
    motion_controller.updateLeftCount();
}

void setup() {
    ITimer0.attachInterruptInterval(TIMER0_INTERVAL_MS * 1000, TimerHandler0);
    ITimer1.attachInterruptInterval(SPEED_TIMER_INTERVAL_MS * 1000, TimerHandler1);
    attachInterrupt(digitalPinToInterrupt(ENC_C1_PIN_L), updateLeftCount, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENC_C1_PIN_R), updateRightCount, CHANGE);

    api.createPositionCommand(1, 0, 1);

    // while (0 == api.commandListSize()) {
    //     Serial.println("Waiting for the first command...");
    //     api.parseInputAndCreateCommand();
    // }
}

void loop() {
    // delay(1000);
    // api.parseInputAndCreateCommand();

    // last_command_done = motion_controller.command_state_machine(current_x, current_y, current_v, current_w);

    // if (0 != api.commandListSize() && true == last_command_done) {
    //     pico_command_t current_command = api.getNextCommand();

    //     current_x = current_command.x;
    //     current_y = current_command.y;
    //     current_v = current_command.v;
    //     current_w = current_command.w;
    // }
}
