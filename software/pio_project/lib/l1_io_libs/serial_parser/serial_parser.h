
#pragma once

#include "Arduino.h"
#include <string.h>

#define BUFFER_SIZE 64

enum Direction {
    NONE,
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

struct PicoCommand {
    Direction direction;
    int speed;
    int distance;
};

class SerialParser {

  private:
    // Class variables
    char buffer_[BUFFER_SIZE];  // Buffer for storing serial input
    char command_[BUFFER_SIZE]; // String for storing command

  public:
    // Constructor
    SerialParser() {
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
        parsed_args.direction = NONE;
        parsed_args.speed = 0;
        parsed_args.distance = 0;

        char *serial_input = buffer_;
        char *unparsed_command = NULL;
        size_t command_len = 0;

        printf("Parse command: %s\n", buffer_);

        // Get the start and end indices of the argument list
        char *start_idx = strchr(serial_input, '<');
        char *end_idx = strchr(serial_input, '>');
        if (!start_idx || !end_idx) {
            PicoCommand error_command;
            error_command.direction = NONE;

            return error_command;
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

        // Iterate over the parts and split each part by the colon character
        for (int i = 0; i < num_parts; i++) {
            char *key_value[2];
            key_value[0] = strtok(parts[i], ":");
            key_value[1] = strtok(NULL, ":");

            // If the part was correctly split into a key and value pair, add it to the unordered map
            if (key_value[0] && key_value[1]) {
                if (strcmp(key_value[0], "DIR") == 0) {
                    if (strcmp(key_value[1], "LEFT") == 0) {
                        parsed_args.direction = LEFT;
                    } else if (strcmp(key_value[1], "RIGHT") == 0) {
                        parsed_args.direction = RIGHT;
                    } else if (strcmp(key_value[1], "FORWARD") == 0) {
                        parsed_args.direction = FORWARD;
                    } else if (strcmp(key_value[1], "BACKWARD") == 0) {
                        parsed_args.direction = BACKWARD;
                    }
                } else if (strcmp(key_value[0], "SPEED") == 0) {
                    parsed_args.speed = atoi(key_value[1]);
                } else if (strcmp(key_value[0], "DIST") == 0) {
                    parsed_args.distance = atoi(key_value[1]);
                }
            }
        }

        free(unparsed_command);

        // Return the parsed PicoCommand struct
        return parsed_args;
    }

    void GetCommand() {
        ReadInput();
        ParseCommand();
    }
};
