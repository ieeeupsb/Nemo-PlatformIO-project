// ssh ieeeupsb@192.168.0.162
// pass 1234

#include "Arduino.h"
#include "encoder_reader.h"
#include "micro_controller_unit.h"

// MicroControllerUnit &mcu = MicroControllerUnit::getInstance();

// EncoderReader left_encoder_reader(ENC_C1_PIN_L, ENC_C2_PIN_L);
// EncoderReader right_encoder_reader(ENC_C1_PIN_R, ENC_C2_PIN_R);

// volatile int speed_counter_ = 0;

// void updateCount() {
//     // Read the values of the A and B pins
//     int a_state = digitalRead(ENC_C1_PIN_L);
//     int b_state = digitalRead(ENC_C2_PIN_L);

//     // Update the counter based on the states of the A and B pins
//     if (a_state == HIGH && b_state == LOW) {
//         speed_counter_++;
//     } else if (a_state == LOW && b_state == HIGH) {
//         speed_counter_--;
//     }
// }

// void setup() {
//     Serial.begin(9600);
//     pinMode(ENC_C1_PIN_L, INPUT);
//     pinMode(ENC_C2_PIN_L, INPUT);
//     attachInterrupt(digitalPinToInterrupt(ENC_C1_PIN_L), updateCount, CHANGE);
// }

// #define TIME_INTERVAL 1000

// void loop() {
//     Serial.print("rpm:");
//     delay(200);
//     Serial.println((speed_counter_));
// }

#define encoder0PinA ENC_C1_PIN_L
#define encoder0PinB ENC_C2_PIN_L
volatile int encoder0Pos = 0;

void doEncoder() {
    if (digitalRead(encoder0PinA) == digitalRead(encoder0PinB)) {
        encoder0Pos++;
    } else {
        encoder0Pos--;
    }
}

void setup() {
    pinMode(encoder0PinA, INPUT);
    pinMode(encoder0PinB, INPUT);
    attachInterrupt(digitalPinToInterrupt(encoder0PinA), doEncoder, CHANGE);
}

void loop() {
    Serial.println(encoder0Pos, DEC);
    delay(100);
}
