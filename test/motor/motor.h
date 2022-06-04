#pragma once
#include <Arduino.h>
#include <ESP32Encoder.h>

#define MIN_PWM 120
#define MAX_PWM 150

#define LEFT_MOTOR_CHANNEL 0
#define RIGHT_MOTOR_CHANNEL 1

#define WALK_CONST 3.43
#define ROTATION_CONST (2120.0 / 360.0)

#define FORWARD 1
#define BACKWARDS 0
#define CLOCKWISE 1
#define ANTI_CLOCKWISE -1

class Motor {
  public:
    void setup(uint8_t dc_motor_1_pin, uint8_t dc_motor_2_pin,
               uint8_t enable_pin, uint8_t channel, int enc1_pin, int enc2_pin);
    void set_speed(uint8_t _dir, uint32_t _pwmVal);
    void stop();
    ESP32Encoder encoder;
    uint32_t pwmVal;
    uint8_t dir;
    float get_speed();
    int refresh(int pwm_dif);
    void set_pwm(unsigned int _pwmVal);
    float speed = 0;
    int pwm_average = 0;

  private:
    uint8_t pwm_channel;
    double pwm_frequency = 5000;
    uint8_t resolution_bits = 8;

    uint8_t dc_motor_1;
    uint8_t dc_motor_2;

    float previous_tick_number = 0;
    float previous_time = 0;
};

class SimplePID {
  private:
    float kp, kd, ki, umax; // Parameters
    float eprev, eintegral; // Storage

  public:
    // Constructor
    SimplePID() : kp(1), kd(0), ki(0), umax(255), eprev(0.0), eintegral(0.0) {}

    // A function to set the parameters
    void setParams(float kpIn, float kdIn, float kiIn, float umaxIn) {
        kp = kpIn;
        kd = kdIn;
        ki = kiIn;
        umax = umaxIn;
    }

    // A function to compute the control signal
    void evalu(int value, int target, float deltaT, int &pwmVal_, int &dir) {
        // error
        int e = target - value;

        // derivative
        float dedt = (e - eprev) / (deltaT);

        // integral
        eintegral = eintegral + e * deltaT;

        // control signal
        float u = kp * e + kd * dedt + ki * eintegral;

        // motor power
        pwmVal_ = (int)fabs(u);
        if (pwmVal_ > umax) {
            pwmVal_ = umax;
        }

        // motor direction
        if (u < 0) {
            dir = BACKWARDS;
        }
        dir = FORWARD;

        // store previous error
        eprev = e;
    }
};

void motors_setup();
void move_forward();
void motor_test();
void slow_down();
void speed_up();
void setMotor(int dir, int pwmVal, int pwm_channel, int in1, int in2);
void setLeftMotor(uint8_t dir, uint32_t pwmVal);
void stopLeftMotor();
void setRightMotor(uint8_t dir, uint32_t pwmVal);
void stopRightMotor();
void rotate(int degrees);
void walk(int millimeters, int direction);