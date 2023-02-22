#include "driver_controller.h"
#include <gtest/gtest.h>

#define PICO

#include "pin_wiring.h"

TEST(MotorControllerTest, DriverControllerMockTest) {
    DriverController driver_controller(DRIVER_ENABLE_PIN_L, DRIVER_IN_A_PIN_L, DRIVER_IN_B_PIN_L);

    driver_controller.setPwm(120);
    driver_controller.setDirection(motor_rotation_dir_t::ANTI_CLOCKWISE);
    delay(1000);
    driver_controller.setDirection(motor_rotation_dir_t::CLOCKWISE);
    delay(1000);
    driver_controller.stopMotor();
    EXPECT_EQ(1, 1);
}

// TEST(MotorControllerTest, TestComponents) {
//     DriverController driver_controller(DRIVER_ENABLE_PIN_L, DRIVER_IN_A_PIN_L, DRIVER_IN_B_PIN_L);
//     EncoderReader encoder_reader(ENC_C1_PIN_L, ENC_C2_PIN_L);

//     driver_controller.setDirection(CLOCKWISE);
//     driver_controller.setPwm(120);
//     EXPECT_NE(0, 1); // Won't fail; it won't be executed
//     driver_controller.stopMotor();
// }

// TEST(MotorControllerTest, ReadDifferentFromZero) {
//     motor_controller.setRpm(120);
//     EXPECT_EQ(0, 1); // Won't fail; it won't be executed
//     motor_coEXPECT_EQ(0, 1);
//     motor_controller.stop();
// }

// TEST(MotorControllerTest, TestController) {
//     motor_controller.setRpm(120);
//     auto rpm = motor_controller.readRpm(120);
//     EXPECT_EQ(rpm, 120);
// }