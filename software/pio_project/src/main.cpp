// ssh ieeeupsb@192.168.0.162
// pass 1234

#include "Arduino.h"
#include "encoder_reader.h"
#include "micro_controller_unit.h"

MicroControllerUnit &mcu = MicroControllerUnit::getInstance();

// // EncoderReader left_encoder_reader(ENC_C1_PIN_R, ENC_C2_PIN_R);
// EncoderReader right_encoder_reader(ENC_C1_PIN_R, ENC_C2_PIN_R);

volatile int speed_counter_ = 0;

void updateCount() {
    // // Read the values of the A and B pins
    // int a_state = digitalRead(ENC_C1_PIN_R);
    // int b_state = digitalRead(ENC_C2_PIN_R);

    // // Update the counter based on the states of the A and B pins
    // if (a_state == b_state) {
    //     speed_counter_++;
    // } else {
    //     speed_counter_--;
    // }
    right_encoder_reader.updateCount();
}

void setup() {
    Serial.begin(9600);
    pinMode(ENC_C1_PIN_R, INPUT);
    pinMode(ENC_C2_PIN_R, INPUT);
    attachInterrupt(digitalPinToInterrupt(ENC_C1_PIN_R), updateCount, CHANGE);
}

#define TIME_INTERVAL 1000

void loop() {
    Serial.print("rpm:");
    delay(200);
    Serial.println(right_encoder_reader.getCount());
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