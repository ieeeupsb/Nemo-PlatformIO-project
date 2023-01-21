#define PICO

#include "driver_controller.h"
#include "pin_wiring.h"
#include <gtest/gtest.h>

TEST(DummyTest, ShouldPass) {
    EXPECT_EQ(1, 1);
}

void Sub1(int n) {
    EXPECT_EQ(n, 1);
}

TEST(FooTest, Bar) {
    {
        SCOPED_TRACE("A"); // This trace point will be included in
                           // every failure in this scope.
        Sub1(1);
    }
    // Now it won't.
    Sub1(9);
}

// TEST(SkipTest, DoesSkip) {
//     GTEST_SKIP() << "Skipping single test";
//     EXPECT_EQ(0, 1); // Won't fail; it won't be executed
// }

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

#if defined(ARDUINO)
#include <Arduino.h>

void setup() {
    // should be the same value as for the `test_speed` option in "platformio.ini"
    // default value is test_speed=115200
    Serial.begin(115200);

    // ::testing::InitGoogleTest();
}

void loop() {
    // Run tests
    // if (RUN_ALL_TESTS())
    // ;
}

#else
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    if (RUN_ALL_TESTS())
        ;
    // Always return zero-code and allow PlatformIO to parse results
    return 0;
}
#endif