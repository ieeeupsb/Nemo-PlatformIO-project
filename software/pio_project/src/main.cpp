

#define PICO

// #include "micro_controller_unit.h"
#include "driver_controller.h"
#include "pin_wiring.h"
#include <rp2040.h>

// mcu &MicroControllerUnit = MicroControllerUnit::getInstance();

void start_timer_microseconds(uint32_t fire_time_microseconds, void (*callback)(void)) {
    /* Set the timer to fire every fire_time_microseconds */
    TIMER1_LOAD = RP2040_CLOCK_FREQ / (1000000 / fire_time_microseconds);
    TIMER1_CONTROL = TIMER1_CONTROL_ENABLE | TIMER1_CONTROL_IE | TIMER1_CONTROL_PRESCALE_1;
    TIMER1_CLEAR = 0;

    /* Set the interrupt handler for the timer */
    interrupt_attach(INTERRUPT_TIMER1, callback);
    interrupt_enable(INTERRUPT_TIMER1);
}

void start_timer_milliseconds(uint32_t fire_time_milliseconds, void (*callback)(void)) {
    /* Set the timer to fire every fire_time_milliseconds */
    TIMER1_LOAD = RP2040_CLOCK_FREQ / (1000 / fire_time_milliseconds);
    TIMER1_CONTROL = TIMER1_CONTROL_ENABLE | TIMER1_CONTROL_IE | TIMER1_CONTROL_PRESCALE_1;
    TIMER1_CLEAR = 0;

    /* Set the interrupt handler for the timer */
    interrupt_attach(INTERRUPT_TIMER1, callback);
    interrupt_enable(INTERRUPT_TIMER1);
}

DriverController driver_controller(DRIVER_ENABLE_PIN_L, DRIVER_IN_A_PIN_L, DRIVER_IN_B_PIN_L);

int test_pwm = 0;

void test_function() {
    test_pwm += 10;
    driver_controller.setPwm(test_pwm);
}

int main(void) {

    driver_controller.setPwm(0);
    driver_controller.setDirection(motor_rotation_dir_t::ANTI_CLOCKWISE);

    start_timer_milliseconds(500, test_function);
    while (1) {
        __asm__("wfi");
    }
}
