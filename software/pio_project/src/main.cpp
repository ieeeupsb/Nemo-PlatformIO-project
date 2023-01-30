// ssh ieeeupsb@192.168.0.162
// pass 1234

#include "Arduino.h"
#include "PID_v1.h"
#include "RPi_Pico_TimerInterrupt.h"
#include "encoder_reader.h"
#include "micro_controller_unit.h"
#include "pidautotuner.h"

#define TIMER0_INTERVAL_MS 200
RPI_PICO_Timer ITimer0(0);

MicroControllerUnit &mcu = MicroControllerUnit::getInstance();

// // EncoderReader left_encoder_reader(ENC_C1_PIN_R, ENC_C2_PIN_R);
EncoderReader right_encoder_reader(ENC_C1_PIN_R, ENC_C2_PIN_R);
DriverController right_driver_controller(DRIVER_ENABLE_PIN_R, DRIVER_IN_A_PIN_R, DRIVER_IN_B_PIN_R);

double Setpoint, Input, Output;

// double Kp = 0.7, Ki = 0, Kd = 0;
// PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

volatile int speed_counter_ = 0;
volatile float speed;

bool TimerHandler0(struct repeating_timer *t) {
    right_encoder_reader.updateSpeed(TIMER0_INTERVAL_MS, speed_counter_);
    speed = (float)speed_counter_ / (float)TIMER0_INTERVAL_MS;
    speed_counter_ = 0;

    return true;
}

void updateCount() {
    int a_state = digitalRead(ENC_C1_PIN_R);
    int b_state = digitalRead(ENC_C2_PIN_R);

    if (a_state == b_state) {
        speed_counter_++;
    } else {
        speed_counter_--;
    }
}

void setup() {
    Serial.begin(9600);

    pinMode(ENC_C1_PIN_R, INPUT);
    pinMode(ENC_C2_PIN_R, INPUT);
    attachInterrupt(digitalPinToInterrupt(ENC_C1_PIN_R), updateCount, CHANGE);
    right_driver_controller.setPwm(70);
    right_driver_controller.setDirection(motor_rotation_dir_t::CLOCKWISE);
    ITimer0.attachInterruptInterval(TIMER0_INTERVAL_MS * 1000, TimerHandler0);
    Setpoint = 2;

    // turn the PID on
    // myPID.SetMode(AUTOMATIC);
}

#define TIME_INTERVAL 1000

int speed_control_state = 0;

void loop() {
    switch (speed_control_state) {
    case 0:
        Input = right_encoder_reader.getRpm();
        Serial.println("Input rpm: ");
        Serial.println(speed);
        // speed_control_state = 1;
        break;
    case 1:
        // myPID.Compute();
        // Serial.println("Output: ");
        // Serial.println(Output);

        // right_driver_controller.setPwm(Output);
        speed_control_state = 0;
    default:
        break;
    }
}

// void setup() {
//     Serial.begin(115200);
//     pinMode(ENC_C1_PIN_R, INPUT);
//     pinMode(ENC_C2_PIN_R, INPUT);
//     pinMode(ENC_C1_PIN_R, INPUT);
//     pinMode(ENC_C2_PIN_R, INPUT);
// }

// void loop() {
//     Serial.print("ENC_C1_PIN_R:");
//     Serial.println(digitalRead(ENC_C1_PIN_R));
//     Serial.print("ENC_C2_PIN_R:");
//     Serial.println(digitalRead(ENC_C2_PIN_R));
//     Serial.print("ENC_C1_PIN_R:");
//     Serial.println(digitalRead(ENC_C1_PIN_R));
//     Serial.print("ENC_C2_PIN_R:");
//     Serial.println(digitalRead(ENC_C2_PIN_R));
//     Serial.println("\n\n\n\n\n\n");
//     delay(1000);
// }