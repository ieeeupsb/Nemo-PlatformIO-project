#pragma once

#include "Arduino.h"

class Encoder {
  public:
    // Constructor
    Encoder() {

        counter_ = 0;
    }

    Encoder(int pin_a, int pin_b) {
        // Save the pin numbers
        pin_a_ = pin_a;
        pin_b_ = pin_b;

        // Set the pins as inputs
        pinMode(pin_a_, INPUT);
        pinMode(pin_b_, INPUT);

        // Initialize the counter
        counter_ = 0;
    }

    // Function to update the encoder count
    void Update() {
        // Read the values of the A and B pins
        int a_state = digitalRead(pin_a_);
        int b_state = digitalRead(pin_b_);

        // Update the counter based on the states of the A and B pins
        if (a_state == HIGH && b_state == LOW) {
            counter_++;
        } else if (a_state == LOW && b_state == HIGH) {
            counter_--;
        }
    }

    // Function to get the current encoder count
    int GetCount() {
        return counter_;
    }

    void RestartCounter() {
        counter_ = 0;
        return;
    }

  private:
    int pin_a_;
    int pin_b_;
    int counter_;
};