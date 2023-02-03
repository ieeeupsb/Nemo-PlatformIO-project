import serial
import cv2
import numpy as np
import camera
from aruco_functions import *

# ACE parameters

dictionary = cv2.aruco.Dictionary_get(cv2.aruco.DICT_5X5_1000)
logi_filename = "calibration.pckl"
marker_lenght = 0.15
MAP_X_MIN, MAP_X_MAX, MAP_Y_MIN, MAP_Y_MAX = 0, 2, 0, 2


class ArucoMarker:
    def __init__(self, marker_id, corners, marker_lenght, camera_matrix, dist_coefs):
        self.marker_id = marker_id
        self.corners = corners

        position = extract_marker_position(
            corners, marker_lenght, camera_matrix, dist_coefs)

        # Calculate the distance and angle to the marker
        self.distance = np.linalg.norm(position)
        self.angle = np.arctan2(position[1], position[0])


def camera_calibration():
    return "calibration.npz"


def calculate_xy_distance(distance, angle):
    x = distance * np.cos(angle)
    y = distance * np.sin(angle)
    return round(x, 2), round(y, 2)


def extract_marker_position(corners, marker_lenght, camera_matrix, dist_coefs):
    # Extract the pose of the marker
    rvec, tvec, _ = cv2.aruco.estimatePoseSingleMarkers(
        corners, marker_lenght, camera_matrix, dist_coefs)

    # Convert the rotation vector to a rotation matrix
    R, _ = cv2.Rodrigues(rvec)

    # Extract the position of the marker
    position = -np.matrix(R).T * np.matrix(tvec)

    return position


def ids_distances_and_angles_list(image, camera_matrix, dist_coefs):
    # Convert the image to grayscale
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    # Detect the markers in the image
    corners, ids, _ = cv2.aruco.detectMarkers(gray, dictionary)

    # Initialize a dictionary to store the distances and angles for each marker
    ids_distances_and_angles = {}

    # Iterate over each detected marker
    for i, marker_id in enumerate(ids):
        # Extract the position
        position = extract_marker_position(
            corners, marker_lenght, camera_matrix, dist_coefs)

        # Calculate the distance and angle to the marker
        distance = np.linalg.norm(position)
        angle = np.arctan2(position[1], position[0])

        # Store the distance and angle in the dictionary
        ids_distances_and_angles[i] = (marker_id, distance, angle)

    return ids_distances_and_angles


def ids_x_pos_y_pos_list(image, camera_matrix, dist_coefs):
    # Convert the image to grayscale
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    # Detect the markers in the image
    corners, ids, _ = cv2.aruco.detectMarkers(gray, aruco_dict)

    # Initialize a dictionary to store the distances and angles for each marker
    ids_x_pos_y_pos = {}

    # Iterate over each detected marker
    for i, marker_id in enumerate(ids):
        # Extract the position
        position = extract_marker_position(
            marker_lenght, camera_matrix, dist_coefs)

        # Calculate the distance and angle to the marker
        distance = np.linalg.norm(position)
        angle = np.arctan2(position[1], position[0])

        x_pos, y_pos = calculate_xy_distance(distance, angle)

        # Store the distance and angle in the dictionary
        ids_x_pos_y_pos[i] = (marker_id, x_pos, y_pos)

    return ids_distances_and_angles


def commands_to_nearest_marker(camera, marker_lenght):

    camera_matrix = camera.cameraMatrix
    dist_coefs = camera.distCoeffs

    # Read the frame and detect markers in the camera
    corners, ids, _ = camera.detectMarkers(dictionary)

    if ids is None:
        print("No markers found")
        return

    # Initialize a dictionary to store the distance and angle for each marker ID
    distances_and_angles = {}
    for i, marker_id in enumerate(ids):
        # Extract the position of the marker
        position = extract_marker_position(corners,
                                           marker_lenght, camera_matrix, dist_coefs)

        # Calculate the distance and angle to the marker
        distance = np.linalg.norm(position)
        angle = np.arctan2(position[1], position[0])

        # Store the distance and angle for the marker ID in the dictionary
        distances_and_angles[marker_id] = (distance, angle)

    # Find the marker ID with the minimum distance
    nearest_marker_id = min(distances_and_angles,
                            key=lambda x: distances_and_angles[x][0])

    # Get the distance and angle for the nearest marker
    nearest_marker_distance = distances_and_angles[nearest_marker_id][0]
    nearest_marker_angle = distances_and_angles[nearest_marker_id][1]

    # Calculate the x and y distance to the nearest marker
    x_distance, y_distance = calculate_xy_distance(
        nearest_marker_distance, nearest_marker_angle)

    commands = create_command_str(x_distance, y_distance)

    # Print the list of commands
    return commands


def linear_and_angular_speed_to_marker(camera, map, aruco_dict):
    linear_speed = 0
    angular_speed = 0

    corners, ids, _ = camera.detectMarkers(aruco_dict)

    # Compute the pose of each marker
    rvecs, tvecs, _ = camera.estimatePoseSingleMarkers(corners, marker_lenght)

    if tvecs is not None:
        linear_speed = np.linalg.norm(tvecs[0])

    if rvecs is not None:
        angular_speed = np.linalg.norm(rvecs[0])

    return linear_speed, angular_speed


if __name__ == "__main__":

    # main()
    ser = serial.Serial('/dev/ttyACM0')
    test_marker1 = camera.ArucoMarker(dictionary, None, 35, marker_lenght)
    test_marker2 = camera.ArucoMarker(dictionary, None, 5, marker_lenght)

    ace_map = camera.ArucoMap(MAP_X_MIN, MAP_X_MAX, MAP_Y_MIN, MAP_Y_MAX)

    ace_map.addMarker(test_marker1, 1, 0.5)
    ace_map.addMarker(test_marker2, 0.5, 0.5)

    logi_camera = camera.Camera(0, logi_filename)

    # logi_camera.start()

    # while (logi_camera.isOpened()):

    #     linear_speed, angular_speed = linear_and_angular_speed_to_marker(
    #         logi_camera, ace_map, dictionary)

    #     if linear_speed != 0 or angular_speed != 0:
    #         command_to_send=create_command(0, 0, linear_speed, angular_speed)
    #         send_command(command_to_send)
    #     # elif ser.in_waiting:
    #     #     line = ser.readline()
    #     #     print(line)

    while (logi_camera.isOpened()):

        target_x, target_y = nearest_marker_x_y = (logi_camera, dictionary)
        linear_speed, angular_speed = trajectory_calulator_straight_lines(
            target_x, target_y)

        if linear_speed != 0 or angular_speed != 0:
            command_to_send = create_command(0, 0, linear_speed, angular_speed)
            send_command(command_to_send, ser)
        # elif ser.in_waiting:
        #     line = ser.readline()
        #     print(line)


ser.close()
