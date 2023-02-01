#ifndef __MCU_API_H__
#define __MCU_API_H__

#include "Arduino.h"
#include <list>
#include <string.h>

#define MAX_FAILED_COMMANDS
#define BUFFER_SIZE 64
#define TIMEOUT_MS 20000

struct pico_command_t {
    double x = 0;
    double y = 0;
    double v = 0;
    double w = 0;
};

class McuAPI {

  private:
    std::list<String> input_buffer_;
    std::list<pico_command_t> command_list;
    unsigned int error_counting_ = 0;
    int info_list_size_delete_me = 3;

    void readFromSerial() {
        if (Serial.available() > 0) {
            // read the incoming string:
            String incomming = Serial.readString();
            input_buffer_.push_back(incomming);

            return;
        }

        if (error_counting_ > TIMEOUT_MS / TIMER0_INTERVAL_MS) {

            send_error_command();
            error_counting_ = 0;
        }
    }

    void createNewCommand(double x, double y, double v, double w) {
        pico_command_t new_command;

        new_command.x = x;
        new_command.y = y;
        new_command.v = v;
        new_command.w = w;

        // Serial.print("x:");
        // Serial.println(x);
        // Serial.print("y:");
        // Serial.println(y);
        // Serial.print("v:");
        // Serial.println(v);
        // Serial.print("w:");
        // Serial.println(w);

        command_list.push_back(new_command);
    }

  public:
    // Constructor
    McuAPI(int baud_rate) {
        // Initialize serial port
        Serial.begin(baud_rate);
    }

    void send_error_command() {
        Serial.println("Sending error command");
        pico_command_t empty_command;
        input_buffer_.push_back("x:0;y:0;v:0;w:0");
    }

    bool parseInputAndCreateCommand() { // use in data treatement
        String incoming;

        if (input_buffer_.size() < 1) {
            return false;
        }
        incoming = *input_buffer_.begin();
        input_buffer_.pop_front();

        int x_index = incoming.indexOf("x:");
        int y_index = incoming.indexOf("y:");
        int v_index = incoming.indexOf("v:");
        int w_index = incoming.indexOf("w:");

        if (x_index == -1 || y_index == -1 || v_index == -1 || w_index == -1) {

            // if (error_counting_ > MAX_FAILED_COMMANDS) {

            //     pico_command_t empty_command;
            //     command_list.push_front(empty_command);
            //     Serial.println(error_counting_);
            //     Serial.end();
            // }
            // FIXME
            return false;
        }
        Serial.println("ACK");

        int semi_colon_index = 0;
        error_counting_ = 0;

        semi_colon_index = incoming.indexOf(";");
        String x_substring = incoming.substring(2, semi_colon_index);
        incoming = incoming.substring(semi_colon_index + 1);

        semi_colon_index = incoming.indexOf(";");
        String y_substring = incoming.substring(2, semi_colon_index);
        incoming = incoming.substring(semi_colon_index + 1);

        semi_colon_index = incoming.indexOf(";");
        String v_substring = incoming.substring(2, semi_colon_index);
        incoming = incoming.substring(semi_colon_index + 1);

        semi_colon_index = incoming.indexOf(";");
        String w_substring = incoming.substring(2, semi_colon_index + 1);

        createNewCommand(x_substring.toDouble(), y_substring.toDouble(), v_substring.toDouble(), w_substring.toDouble());

        return true;
    }

    void timerHandler(double left_wheel_speed, double right_wheel_speed) {
        readFromSerial();
        error_counting_++;
        // sendInfo(left_wheel_speed, right_wheel_speed);
    }

    void sendInfo(double left_wheel_speed, double right_wheel_speed) {
        Serial.print("left wheel speed = ");
        Serial.println(left_wheel_speed);
        Serial.print("right wheel speed = ");
        Serial.println(right_wheel_speed);
    }

    int commandListSize() {
        return command_list.size();
    }

    pico_command_t getNextCommand() {
        if (command_list.size() <= 0) {
            pico_command_t empty_command;
            Serial.println("command_list is empty.");
            return empty_command;
        }

        auto next_command = command_list.begin();
        command_list.pop_front();

        return *next_command;
    }

    void createPositionCommand(double x, double y, double v) {
        createNewCommand(x, y, v, 0);
    }
    void createTrajectoryCommand(double v, double w) {
        createNewCommand(0, 0, v, w);
    }
};

#endif
