import numpy as np
import math


def nearest_marker_x_y(camera, map, aruco_dict):
    linear_speed = 0
    angular_speed = 0

    corners, ids, _ = camera.detectMarkers(aruco_dict)

    # Compute the pose of each marker
    rvecs, tvecs, _ = camera.estimatePoseSingleMarkers(corners, marker_lenght)

    dist = []
    for i in range(len(tvecs)):

        dist.append(np.linalg.norm(tvecs[i]))

    if tvecs is not None:
        min_dist = np.min(dist)

    if rvecs is not None:
        angular_speed = np.linalg.norm(rvecs[0])

    return linear_speed, angular_speed


def speed_calculator(distance, MAX_SPEED, BRACKING_FACTOR):
    ROBOT_MIN_SPEED = 0.1
    if (MAX_SPEED == 0):
        speed = ROBOT_MIN_SPEED

        speed = (MAX_SPEED - BRACKING_FACTOR /
                 (distance + BRACKING_FACTOR / MAX_SPEED))

        if (speed < ROBOT_MIN_SPEED):
            speed = ROBOT_MIN_SPEED

        if (speed > MAX_SPEED):
            speed = MAX_SPEED

    return speed


def trajectory_calulator_straight_lines(target_x, target_y):

    MAX_SPEED = 0.4
    BRACKING_FACTOR = 0

    distance = math.sqrt(pow(target_x, 2) + pow(target_y, 2))

    if (0 == distance):

        linear_speed = 0
        angular_speed = 0

        return linear_speed, angular_speed

    desire_angle = math.atan2(0, target_x - target_y)
    angle_error = desire_angle

    speed = speed_calculator(distance, MAX_SPEED, BRACKING_FACTOR)

    if (angle_error > 0):
        linear_speed = 0
        angular_speed = speed

    if (angle_error == 0):
        linear_speed = 0
        angular_speed = speed

    if (angle_error < 0):
        trajectory.linear_speed = speed
        angular_speed = 0

    return linear_speed, angular_speed


def create_command(x, y, v, w):
    return "x:" + str(x) + ";y:" + str(y) + ";v:"+str(v) + ";w:" + str(w)


def send_command(command):
    ser.write(command.encode())
    print("Sending commmand: " + command)
