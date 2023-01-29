#include "../lib/motion_controller/motion_controller.h"

#include <cassert>

void test_trajectory_calulator() {
    // Test input
    coordinate_t estimated_coordinate = {0, 0};
    coordinate_t target_coordinate = {10, 10};

    // Call function
    trajectory_t result = trajectory_calulator(estimated_coordinate, target_coordinate);

    // Expected output
    trajectory_t expected_result = {sqrt(200), atan2(10, 10)};

    // Compare output
    assert(result.linear_speed == expected_result.linear_speed);
    assert(result.angular_speed == expected_result.angular_speed);
}

// void test_wheels_linear_speed_calculator() {
//     // Test input
//     trajectory_t target_trajectory = {10, 0.5};
//     float wheel_base = 2.0;

//     // Call function
//     wheels_speed_t result = wheels_linear_speed_calculator(target_trajectory, wheel_base);

//     // Expected output
//     wheels_speed_t expected_result = {9.0, 11.0};

//     // Compare output
//     assert(result.left_wheel_speed == expected_result.left_wheel_speed);
//     assert(result.right_wheel_speed == expected_result.right_wheel_speed);
// }
