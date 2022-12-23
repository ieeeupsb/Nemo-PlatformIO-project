
#pragma once

#include "Arduino.h"
#include <string>
#include <unordered_map>

#define BUFFER_SIZE 64

enum class Direction {
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

        std::string serial_input = buffer_;
        std::unordered_map<std::string, std::string>
            args;

        Serial.print("Parse command:");
        Serial.println(buffer_);

        // Get the start and end indices of the argument list
        size_t start_idx = serial_input.find('<') + 1;
        size_t end_idx = serial_input.find('>');
        if (start_idx == std::string::npos || end_idx == std::string::npos) {
            // Invalid string formatDOWN
            Serial.println("Invalid string format");
        }
        std::string unparsed_command = serial_input.substr(start_idx + 1, end_idx - start_idx - 1);

        Serial.println(unparsed_command.c_str());

        //     std::unordered_map<std::string, std::string> args;

        //     // Split the input string by semicolons
        //     std::vector<std::string> parts = Split(input, ";");

        //     // Iterate over the parts and split each part by the colon character
        //     for (std::string part : parts) {
        //         // Split the part by the colon character
        //         std::vector<std::string> key_value = Split(part, ":");
        //         // If the part was correctly split into a key and value pair, add it to the unordered map
        //         if (key_value.size() == 2) {
        //             args[key_value[0]] = key_value[1];
        //         }
        //     }

        //     // Create a PicoCommand struct to store the parsed information
        //     PicoCommand parsed_args;

        //     // Try to parse the direction from the input string
        //     if (args.count("DIR")) {
        //         std::string dir = args["DIR"];
        //         if (dir == "LEFT") {
        //             parsed_args.direction = Direction::LEFT;
        //         } else if (dir == "RIGHT") {
        //             parsed_args.direction = Direction::RIGHT;
        //         } else if (dir == "FORWARD") {
        //             parsed_args.direction = Direction::FORWARD;
        //         } else if (dir == "BACKWARD") {
        //             parsed_args.direction = Direction::BACKWARD;
        //         } else {
        //             parsed_args.direction = Direction::NONE;
        //         }
        //     } else {
        //         parsed_args.direction = Direction::NONE;
        //     }

        //     // Try to parse the speed from the input string
        //     if (args.count("SPEED")) {
        //         parsed_args.speed = std::stoi(args["SPEED"]);
        //     } else {
        //         parsed_args.speed = 0;
        //     }

        //     // Try to parse the distance from the input string
        //     if (args.count("DIST")) {
        //         parsed_args.distance = std::stoi(args["DIST"]);
        //     } else {
        //         parsed_args.distance = 0;
        //     }

        //     // Return the parsed PicoCommand struct
        //     return parsed_args;
    }

    void GetCommand() {
        ReadInput();
        ParseCommand();
    }
};
