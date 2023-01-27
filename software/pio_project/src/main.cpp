
/* Kernel includes. */
// #include "FreeRTOS.h"

// ssh ieeeupsb@192.168.0.162
// pass 1234

/* Kernel includes. */
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

#include "Arduino.h"
#include "pico_pinout.h"

void TaskBlink1(void *pvParameters);

void TaskBlink2(void *pvParameters);

void Taskprint(void *pvParameters);

void setup() {

    // initialize serial communication at 9600 bits per second:
    xTaskCreate(TaskBlink1, "task1", 128, NULL, 1, NULL);
}

void loop() {
}

void TaskBlink1(void *pvParameters) {

    pinMode(8, OUTPUT);

    while (1)

    {

        Serial.println("Task1");

        digitalWrite(8, HIGH);

        vTaskDelay(200 / portTICK_PERIOD_MS);
        digitalWrite(8, LOW);
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}
