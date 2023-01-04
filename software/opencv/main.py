import cv2
import numpy as np
import camera

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


def send_commands(commands):
    print("Sending commands")
    # TODO
    print(commands)


def add_marker_to_map_from_camera(camera, map, aruco_dict):
    TOP_LEFT_ID = 1
    TOP_RIGHT_ID = 2
    BOTTON_LEFT_ID = 3
    BOTTON_RIGHT_ID = 4

    corners, ids, _ = camera.detectMarkers(aruco_dict)

    if ids is None or len(ids) < 2:
        return 0

    idx_ref = None
    if TOP_LEFT_ID in ids:
        reference_marker_x = MAP_X_MIN
        reference_marker_y = MAP_Y_MAX
        idx_ref = np.where(ids == TOP_LEFT_ID)[0]
    elif TOP_RIGHT_ID in ids:
        reference_marker_x = MAP_X_MAX
        reference_marker_y = MAP_Y_MAX
        idx_ref = np.where(ids == TOP_RIGHT_ID)[0]
    elif BOTTON_LEFT_ID in ids:
        reference_marker_x = MAP_X_MIN
        reference_marker_y = MAP_Y_MIN
        idx_ref = np.where(ids == BOTTON_LEFT_ID)[0]
    elif BOTTON_RIGHT_ID in ids:
        reference_marker_x = MAP_X_MAX
        reference_marker_y = MAP_Y_MIN
        idx_ref = np.where(ids == BOTTON_RIGHT_ID)[0]
    else:
        return 0

    # Compute the pose of each marker
    rvecs, tvecs, _ = camera.estimatePoseSingleMarkers(corners, marker_lenght)

    # Convert the rotation vectors to rotation matrices
    Rs = [cv2.Rodrigues(rvec)[0] for rvec in rvecs]

    # Get the pose of the reference marker
    R1 = Rs[idx_ref[0]]
    t1 = tvecs[idx_ref[0]]

    reference_marker_ids = [TOP_LEFT_ID, TOP_RIGHT_ID,
                            BOTTON_LEFT_ID, BOTTON_RIGHT_ID]

    added_markers = 0

    for i, marker_id in enumerate(ids):
        if marker_id in reference_marker_ids:
            print("Reference marker")
        else:
            R2 = Rs[i]
            t2 = tvecs[i]

            # Compute the relative pose of the other marker with respect to reference marker
            R_rel = np.matmul(np.linalg.inv(R1), R2)
            t_rel = t2 - np.matmul(R1, t1)

            rel_x = t_rel[0][0]
            rel_y = t_rel[1][0]
            abs_x = reference_marker_x + rel_x
            abs_y = reference_marker_y + rel_y

        aruco_marker = camera.ArucoMarker(
            aruco_dict, None, marker_id, marker_lenght)
        added_markers = added_markers + 1

        map.addMarker(aruco_marker, abs_x, abs_y)

    return added_markers


def main():

    logi_camera = camera.Camera(1, logi_filename)

    # logi_camera.start()

    while (logi_camera.isOpened()):

        commands_list = commands_to_nearest_marker(logi_camera, marker_lenght)
        if bool(commands_list):
            send_commands(commands_list)


if __name__ == "__main__":

    # main()
    test_marker1 = camera.ArucoMarker(dictionary, None, 35, marker_lenght)
    test_marker2 = camera.ArucoMarker(dictionary, None, 5, marker_lenght)

    ace_map = camera.ArucoMap(MAP_X_MIN, MAP_X_MAX, MAP_Y_MIN, MAP_Y_MAX)

    ace_map.addMarker(test_marker1, 1, 0.5)
    ace_map.addMarker(test_marker2, 0.5, 0.5)

    logi_camera = camera.Camera(1, logi_filename)

    # logi_camera.start()

    while (logi_camera.isOpened()):

        add_marker_to_map_from_camera(logi_camera, ace_map, dictionary)

    ace_map.toImage("maps/ace_map.png")
