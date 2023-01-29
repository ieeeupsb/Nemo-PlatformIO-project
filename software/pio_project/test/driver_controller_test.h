// #pragma once

// #include "driver_controller.h"
// #include <gtest/gtest.h>

// TEST(MotorTest, setPwmTest) {
//     // Set up
//     int enable_ = 12;
//     int in_a_ = 9;
//     int in_b_ = 10;
//     int duty_cycle = 50;

//     // Test
//     setPwm(duty_cycle);

//     // Verify
//     EXPECT_EQ(duty_cycle, enable_);
// }

// TEST(MotorTest, stopMotorTest) {
//     // Set up
//     int enable_ = 12;
//     int in_a_ = 9;
//     int in_b_ = 10;

//     // Test
//     stopMotor();

//     // Verify
//     EXPECT_EQ(LOW, in_a_);
//     EXPECT_EQ(LOW, in_b_);
//     EXPECT_EQ(0, enable_);
// }
// TEST(MotorTest, setPwmTest) {

//     int duty_cycle = constrain(duty_cycle, 0, 255);
//     analogWrite(enable_, duty_cycle);

// }
// TEST(MotorTest, setPwmTest) {
//     Motor motor;
//     int duty_cycle = 0;
//     motor.setPwm(duty_cycle);
//     EXPECT_EQ(motor.getPwm(), duty_cycle);
// }
// TEST(MotorDriverTest, setPwmTest) {
//     MotorDriver driver;

//     // Test duty cycle of 0
//     driver.setPwm(0);
//     EXPECT_EQ(0, driver.getPwm());

//     // Test duty cycle of 255
//     driver.setPwm(255);
//     EXPECT_EQ(255, driver.getPwm());

//     // Test duty cycle of -1 (should be constrained to 0)
//     driver.setPwm(-1);
//     EXPECT_EQ(0, driver.getPwm());

//     // Test duty cycle of 256 (should be constrained to 255)
//     driver.setPwm(256);
//     EXPECT_EQ(255, driver.getPwm());
// }
// TEST(MotorDriverTest, setPwmTest) {
//     int duty_cycle = 0;
//     int expected_duty_cycle = 0;

//     // Test 1: duty_cycle = 0
//     setPwm(duty_cycle);
//     EXPECT_EQ(expected_duty_cycle, duty_cycle);

//     // Test 2: duty_cycle = 255
//     duty_cycle = 255;
//     expected_duty_cycle = 255;
//     setPwm(duty_cycle);
//     EXPECT_EQ(expected_duty_cycle, duty_cycle);

//     // Test 3: duty_cycle = -1
//     duty_cycle = -1;
//     expected_duty_cycle = 0;
//     setPwm(duty_cycle);
//     EXPECT_EQ(expected_duty_cycle, duty_cycle);

//     // Test 4: duty_cycle = 256
//     duty_cycle = 256;
//     expected_duty_cycle = 255;
//     setPwm(duty_cycle);
//     EXPECT_EQ(expected_duty_cycle, duty_cycle);
// }
// TEST(MotorTest, setPwmTest) {

//     // Test 1: duty_cycle is less than 0
//     int duty_cycle = -1;
//     Motor m;
//     m.setPwm(duty_cycle);
//     EXPECT_EQ(0, duty_cycle);

//     // Test 2: duty_cycle is greater than 255
//     duty_cycle = 256;
//     m.setPwm(duty_cycle);
//     EXPECT_EQ(255, duty_cycle);

//     // Test 3: duty_cycle is between 0 and 255
//     duty_cycle = 100;
//     m.setPwm(duty_cycle);
//     EXPECT_EQ(duty_cycle, 100);
// }
// TEST(MotorTest, setPwmTest) {
//     Motor m;
//     m.setPwm(0);
//     EXPECT_EQ(0, m.getPwm());
//     m.setPwm(255);
//     EXPECT_EQ(255, m.getPwm());
//     m.setPwm(128);
//     EXPECT_EQ(128, m.getPwm());
//     m.setPwm(-1);
//     EXPECT_EQ(0, m.getPwm());
//     m.setPwm(256);
//     EXPECT_EQ(255, m.getPwm());
// }

// TEST(MotorDriverTest, setPwmTest) {
//     int duty_cycle = 10;
//     int expected_duty_cycle = 10;

//     MotorDriver motor_driver;
//     motor_driver.setPwm(duty_cycle);

//     EXPECT_EQ(expected_duty_cycle, motor_driver.getPwm());
// }