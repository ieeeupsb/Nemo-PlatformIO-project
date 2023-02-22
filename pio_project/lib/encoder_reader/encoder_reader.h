#pragma once

#include "Arduino.h"

class EncoderReader {
  public:
    EncoderReader(int pin_a, int pin_b)
        : pin_a_(pin_a), pin_b_(pin_b) {

        // Set the pins as inputs
        pinMode(pin_a, INPUT);
        pinMode(pin_b, INPUT);

        // Initialize the counters
        counter_ = 0;
    }

    // Function to update the encoder count
    void updateSpeed(unsigned int enlapsed_time_ms, int counter) {
        // Read the values of the A and B pins
        speed_counter_ = counter_;
        enlapsed_time_ms_ = enlapsed_time_ms;
    }

    float getRpm() {
        // Calculate the current RPM of the motor
        // based on the number of encoder counts and the elapsed time
        // auto count = (float)encoder_reader_.GetSpeedCount();
        // encoder_reader_.RestartSpeedCounter();

        //...not tested
        float rpm = (speed_counter_ / pulses_per_revolution_) * (1000 / enlapsed_time_ms_) * 60;
        //...end of not tested

        // return count;
        return speed_counter_;
    }

    void updateCount() {
        int a_state = digitalRead(pin_a_);
        int b_state = digitalRead(pin_b_);

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
    int speed_counter_;
    volatile int counter_;
    unsigned int enlapsed_time_ms_;
    static constexpr float pulses_per_revolution_ = 400.0; // Number of pulses per revolution
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