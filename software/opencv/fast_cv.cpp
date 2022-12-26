#include <cmath>
#include <iostream>
#include <string>

std::string create_command_str(double x, double y)
{
    std::string direction;
    double speed;
    std::string command_string;
    std::string command_list[2];

    // Determine the direction of the movement
    if (x < 0)
    {
        direction = "LEFT";
    }
    else if (x > 0)
    {
        direction = "RIGHT";
    }

    speed = x / 2; // Assume a speed of 0.5 units/second

    // Create the command string
    command_string = "<DIR:" + direction + ";DIST:" + std::to_string(x) + ";SPEED:" + std::to_string(speed) + ">";
    command_list[0] = command_string;

    if (y < 0)
    {
        direction = "BACKWARD";
    }
    else if (y > 0)
    {
        direction = "FOWARD";
    }

    speed = y / 2; // Assume a speed of 0.5 units/second

    command_string = "<DIR:" + direction + ";DIST:" + std::to_string(y) + ";SPEED:" + std::to_string(speed) + ">";
    command_list[1] = command_string;

    return command_list;
}