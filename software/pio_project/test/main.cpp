
/* Kernel includes. */
// #include "FreeRTOS.h"

// ssh ieeeupsb@192.168.0.162
// pass 1234

/* Kernel includes. */
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "timers.h"

#include "Arduino.h"

#include <PID_v1.h>

#include "micro_controller_unit.h"

#define UPDATE_SPEED_DELAY 1000
#define ROBOT_MOTION_CONTROLLER_DELAY 2000
#define EXCHANGE_DATA_DELAY 3000

void vPrintingTask(void *pvParameters);
void vScanningTask(void *pvParameters);
void vCopyingTask(void *pvParameters);
void vStatusCheckTimerCallback(TimerHandle_t xTimer);

MicroControllerUnit &mcu = MicroControllerUnit::getInstance();

int main(void) {

    /* Create tasks */
    xTaskCreate(update_speed_sm, "update_speed_sm", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(robot_motion_controller_sm, "robot_motion_controller_sm", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(exchange_data_with_raspberry_sm, "exchange_data_with_raspberry_sm", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);

    /* Create timer */
    TimerHandle_t xStatusCheckTimer = xTimerCreate("StatusCheckTimer", pdMS_TO_TICKS(5000), pdTRUE, 0, vStatusCheckTimerCallback);
    xTimerStart(xStatusCheckTimer, 0);

    /* Start the scheduler */
    vTaskStartScheduler();

    return 0;
}

void update_speed_sm(void *pvParameters) {

    while (1) {
        switch (expression) {
        case /* constant-expression */:
            /* code */
            break;

        default:
            break;
        }
        mcu.updateSpeed();
    }
}

void robot_motion_controller_sm(void *pvParameters) {
    while (1) {
        /* Perform machine 2 task */
        printf("Machine 2 is running...\n");
        vTaskDelay(pdMS_TO_TICKS(MACHINE2_DELAY));
    }
}

void exchange_data_with_raspberry_sm(void *pvParameters) {
    while (1) {
        /* Perform machine 1 task */
        printf("Machine 1 is running...\n");
        vTaskDelay(pdMS_TO_TICKS(MACHINE1_DELAY));
    }
}