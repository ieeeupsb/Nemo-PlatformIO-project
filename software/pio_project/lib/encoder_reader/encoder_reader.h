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
        rotation_counter_ = 0;
    }

    // Function to update the encoder count
    float Update(float enlapsed_time) {
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

    // Function to get the current encoder count
    int GetSpeedCount() {
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