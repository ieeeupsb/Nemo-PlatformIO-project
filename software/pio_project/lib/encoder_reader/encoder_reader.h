#pragma once

#include "Arduino.h"

class EncoderReader {
  public:
    EncoderReader(int pin_a, int pin_b) {
        // Save the pin numbers
        pin_a_ = pin_a;
        pin_b_ = pin_b;

        // Set the pins as inputs
        pinMode(pin_a_, INPUT);
        pinMode(pin_b_, INPUT);

        // Initialize the counters
        speed_counter_ = 0;
    }

    // Function to update the encoder count
    float updateSpeed(float enlapsed_time) {
        // Read the values of the A and B pins
        int a_state = digitalRead(pin_a_);
        int b_state = digitalRead(pin_b_);

        // Update the counter based on the states of the A and B pins
        if (a_state == HIGH && b_state == LOW) {
            speed_counter_++;
        } else if (a_state == LOW && b_state == HIGH) {
            speed_counter_--;
        }

        return speed_counter_ / enlapsed_time;
    }

    void updateCount() {
        // Read the values of the A and B pins
        int a_state = digitalRead(pin_a_);
        int b_state = digitalRead(pin_b_);

        // Update the counter based on the states of the A and B pins
        if (a_state == b_state) {
            speed_counter_++;
        } else {
            speed_counter_--;
        }
    }

    // Function to get the current encoder count
    int
    getCount() {
        return speed_counter_;
    }

    void RestartSpeedCounter() {
        speed_counter_ = 0;
        return;
    }

  private:
    int pin_a_;
    int pin_b_;
    volatile int speed_counter_;
};

void blocking_check_encoders_connection_with_serial_messages() {
    //     void setup() {
    //     Serial.begin(115200);
    //     pinMode(ENC_C1_PIN_L, INPUT);
    //     pinMode(ENC_C2_PIN_L, INPUT);
    //     pinMode(ENC_C1_PIN_R, INPUT);
    //     pinMode(ENC_C2_PIN_R, INPUT);
    // }

    // void loop() {
    //     Serial.print("ENC_C1_PIN_L:");
    //     Serial.println(digitalRead(ENC_C1_PIN_L));
    //     Serial.print("ENC_C2_PIN_L:");
    //     Serial.println(digitalRead(ENC_C2_PIN_L));
    //     Serial.print("ENC_C1_PIN_R:");
    //     Serial.println(digitalRead(ENC_C1_PIN_R));
    //     Serial.print("ENC_C2_PIN_R:");
    //     Serial.println(digitalRead(ENC_C2_PIN_R));
    //     Serial.println("\n\n\n\n\n\n");
    //     delay(1000);
    // }
}