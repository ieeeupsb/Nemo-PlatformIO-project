
#pragma once

#include "Arduino.h"
#include <string.h>

#define BUFFER_SIZE 64

struct PicoCommand {
    int x_pos;
    int y_pos;
    int speed;
};

class McuAPI {

  private:
    // Class variables
    char buffer_[BUFFER_SIZE];  // Buffer for storing serial input
    char command_[BUFFER_SIZE]; // String for storing command

  public:
    // Constructor
    McuAPI() {
        // Initialize serial port
        Serial.begin(BAUD_RATE);
    }

    // Method to read serial input into buffer
    char *ReadInput() {
        // Read serial input into buffer
        int index = 0;
        while (Serial.available() > 0 && index < BUFFER_SIZE - 1) {
            buffer_[index++] = Serial.read();
        }
        buffer_[index] = '\0'; // Null terminate the string

        return buffer_;
    }

    // Method to parse command from buffer

    PicoCommand ParseCommand() {
        PicoCommand parsed_args;
        parsed_args.x_pos = 0;
        parsed_args.y_pos = 0;
        parsed_args.speed = 0;

        char *serial_input = buffer_;
        char *unparsed_command = NULL;
        size_t command_len = 0;

        printf("Parse command: %s\n", buffer_);

        // Get the start and end indices of the argument list
        char *start_idx = strchr(serial_input, '<');
        char *end_idx = strchr(serial_input, '>');
        if (!start_idx || !end_idx) {

            return parsed_args;
        }

        command_len = (size_t)(end_idx - start_idx - 1);
        unparsed_command = (char *)malloc(command_len + 1);
        strncpy(unparsed_command, start_idx + 1, command_len);
        unparsed_command[command_len] = '\0';

        Serial.print("COMMAND:");
        Serial.print(unparsed_command);
        Serial.println();

        // Split the input string by semicolons
        char *parts[BUFFER_SIZE];
        int num_parts = 0;
        char *part = strtok(unparsed_command, ";");
        while (part) {
            parts[num_parts++] = part;
            part = strtok(NULL, ";");
        }

        parsed_args.x_pos = atoi(parts[0]);
        parsed_args.y_pos = atoi(parts[1]);
        parsed_args.speed = atoi(parts[2]);

        free(unparsed_command);

        // Return the parsed PicoCommand struct
        return parsed_args;
    }

    void
    GetCommand() {
        ReadInput();
        ParseCommand();
    }
};
