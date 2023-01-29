#pragma once

#include <cmath>

#define ROBOT_MIN_SPEED 0.1
#define ROBOT_MAX_SPEED 2

struct trajectory_t {
    float linear_speed;
    float angular_speed;
};

struct pose_t {
    int x_pos;
    int y_pos;
    float angle_pos;
};

struct wheels_speed_t {
    float left_wheel_speed;
    float right_wheel_speed;
};

pose_t pose_estimator(pose_t current_pose, float enlapsed_time, float left_wheel_speed, float right_wheel_speed, float wheel_base) {

    if (!left_wheel_speed && !right_wheel_speed) {
        return current_pose;
    }

    float linear_speed = (left_wheel_speed + right_wheel_speed) / 2;
    float angular_speed = (right_wheel_speed - left_wheel_speed) / wheel_base;

    pose_t estimated_pose;

    estimated_pose.x_pos = current_pose.x_pos + enlapsed_time * linear_speed * cos(current_pose.angle_pos);
    estimated_pose.y_pos = current_pose.y_pos + enlapsed_time * linear_speed * sin(current_pose.angle_pos);
    estimated_pose.x_pos = current_pose.angle_pos + enlapsed_time * angular_speed;

    return estimated_pose;
}

float speed_calculator(float distance, float max_speed, float braking_factor) {

    if (max_speed == 0) {
        return ROBOT_MIN_SPEED;
    }

    float speed = (max_speed - braking_factor / (distance + braking_factor / max_speed));

    if (speed < ROBOT_MIN_SPEED) {
        return ROBOT_MIN_SPEED;
    }

    if (speed > ROBOT_MAX_SPEED) {

        return ROBOT_MAX_SPEED;
    }

    return speed;
}

trajectory_t trajectory_calulator_straight_lines(pose_t estimated_coordinate, pose_t target_coordinate, float trajectory_max_speed) {

    trajectory_t trajectory;
    double distance = sqrt(pow(target_coordinate.x_pos - estimated_coordinate.x_pos, 2) + pow(target_coordinate.x_pos - estimated_coordinate.y_pos, 2));

    if (0 == distance) {

        trajectory.linear_speed = 0;
        trajectory.angular_speed = 0;

        return trajectory;
    }

    double desire_angle = atan2(estimated_coordinate.x_pos - estimated_coordinate.y_pos, target_coordinate.x_pos - estimated_coordinate.x_pos);
    double angle_error = desire_angle - estimated_coordinate.angle_pos;

    auto speed = speed_calculator(distance, trajectory_max_speed, 1);

    if (angle_error > 0) {
        trajectory.linear_speed = 0;
        trajectory.angular_speed = speed_calculator(distance, trajectory_max_speed, 1);

        return trajectory;
    }

    if (angle_error == 0) {
        trajectory.linear_speed = 0;
        trajectory.angular_speed = speed_calculator(distance, trajectory_max_speed, 1);

        return trajectory;
    }

    if (angle_error < 0) {
        trajectory.linear_speed = speed_calculator(distance, trajectory_max_speed, 1);
        trajectory.angular_speed = 0;

        return trajectory;
    }
}

wheels_speed_t trajectory_to_wheels_speed_converter(trajectory_t trajectory, float wheel_base) {
    wheels_speed_t wheels_speed;

    wheels_speed.left_wheel_speed = trajectory.linear_speed - (wheel_base * trajectory.angular_speed) / 2;
    wheels_speed.right_wheel_speed = trajectory.linear_speed + (wheel_base * trajectory.angular_speed) / 2;

    return wheels_speed;
}