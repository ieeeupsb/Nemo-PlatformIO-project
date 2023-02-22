#pragma once
#include "Arduino.h"

class RaspberryAPI {

  private:
    char data_;

    void receiveData() {
        // Read data from Raspberry Pi
        data_ = Wire.read();
        // Perform actions based on received data
        //...
    }

  public:
    RaspberryAPI() {}
    ~RaspberryAPI() {}
    void connectRaspberry() {
        // Initialize I2C as a slave
        Wire.begin(I2C_SLAVE_ADDRESS);
        // Attach a function to be called when data is received
        Wire.onReceive(receiveData);
    }

    char *getData() {
        return data_;
    }
};