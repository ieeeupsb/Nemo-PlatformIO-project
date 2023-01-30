// ssh ieeeupsb@192.168.0.162
// pass 1234

#include "Arduino.h"
#include "encoder_reader.h"
#include "micro_controller_unit.h"

MicroControllerUnit &mcu = MicroControllerUnit::getInstance();

// // EncoderReader left_encoder_reader(ENC_C1_PIN_R, ENC_C2_PIN_R);
EncoderReader right_encoder_reader(ENC_C1_PIN_R, ENC_C2_PIN_R);
DriverController right_driver_controller(DRIVER_ENABLE_PIN_R, DRIVER_IN_A_PIN_R, DRIVER_IN_B_PIN_R);

volatile int speed_counter_ = 0;

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
    right_driver_controller.setPwm(40);
    right_driver_controller.setDirection(motor_rotation_dir_t::CLOCKWISE);
    // mcu.test_motors();
}

#define TIME_INTERVAL 1000

void loop() {
    Serial.print("rpm:");
    delay(1000);
    right_encoder_reader.updateSpeed(1000);
    Serial.println(right_encoder_reader.getRpm(speed_counter_));
    speed_counter_ = 0;
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