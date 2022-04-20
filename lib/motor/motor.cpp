#include "motor.h"
#include "setup.h"
#include "Arduino.h"
#include "../communication/comm.h"
#include <ESP32Encoder.h>

Motor left_motor;
Motor right_motor;

void motors_setup() {
  ESP32Encoder::useInternalWeakPullResistors=UP; 
  left_motor.setup(DC_MOTOR_1L, DC_MOTOR_2L, ENABLE_L, LEFT_MOTOR_CHANNEL, ENC1_L, ENC2_L);
  right_motor.setup(DC_MOTOR_1R, DC_MOTOR_2R, ENABLE_R, RIGHT_MOTOR_CHANNEL, ENC1_R,ENC2_R);
}

void rotate(int degrees) {
  
  
  int left_speed = NEMO_SPEED;
  int right_speed = NEMO_SPEED;
  left_motor.encoder.setCount(0);
	right_motor.encoder.setCount(0);

  int32_t ticks = (int32_t)((-2200/360.0)*degrees);
  left_motor.set_speed(FORWARD, left_speed);
  right_motor.set_speed(BACKWARDS, right_speed);

  while(right_motor.encoder.getCount() > -ticks) {
  
  }
  left_motor.stop();
  right_motor.stop();
}


void walk(int millimeters, int direction) {
  int left_speed = NEMO_SPEED;
  int right_speed = NEMO_SPEED;
  left_motor.encoder.setCount(0);
	right_motor.encoder.setCount(0);

  int ticks = (int32_t)(3.43 * float(millimeters));
  left_motor.set_speed(FORWARD, left_speed);
  right_motor.set_speed(FORWARD, right_speed);
  
  while( (int32_t)left_motor.encoder.getCount() == ticks ) {
    Serial.println("ddd");
  }
  left_motor.stop();
  right_motor.stop();
}

void Motor::setup(uint8_t dc_motor_1_pin, uint8_t dc_motor_2_pin, uint8_t enable_pin, uint8_t channel, int enc1_pin, int enc2_pin) {
  ledcAttachPin(enable_pin, channel);
  ledcSetup(channel, pwm_frequency, resolution_bits);
  pinMode(dc_motor_1_pin, OUTPUT);
  pinMode(dc_motor_2_pin, OUTPUT);
  digitalWrite(dc_motor_1_pin, LOW);
  digitalWrite(dc_motor_2_pin, LOW);

  pwm_channel = channel;
  dc_motor_1 = dc_motor_1_pin;
  dc_motor_2 = dc_motor_2_pin;

  encoder.attachHalfQuad(enc1_pin, enc2_pin);
}

void Motor::set_speed(uint8_t dir, uint32_t pwmVal) {
  ledcWrite(pwm_channel, pwmVal);
  digitalWrite(dc_motor_1, dir);
  digitalWrite(dc_motor_2, !dir);
}

void Motor::stop() {
  ledcWrite(pwm_channel, 0);
  digitalWrite(dc_motor_1,LOW);
  digitalWrite(dc_motor_2,LOW);
}