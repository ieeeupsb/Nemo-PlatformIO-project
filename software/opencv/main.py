import cv2
import numpy as np
import os
import camera


class ArucoMarker:
    def __init__(self, marker_id, corners, marker_lenght, camera_matrix, dist_coefs):
        self.marker_id = marker_id
        self.corners = corners
        
        position = extract_marker_position(corners, marker_lenght, camera_matrix, dist_coefs)

        # Calculate the distance and angle to the marker
        self.distance = np.linalg.norm(position)
        self.angle = np.arctan2(position[1], position[0])

def camera_calibration():
    return "calibration.npz"

def calculate_xy_distance(distance, angle):
    x = distance * np.cos(angle)
    y = distance * np.sin(angle)
    return round(x, 2), round(y, 2)



def get_calibration_parameters_from_file(calibration_filename):
	# Load the calibration parameters
    
    calibration = np.load(calibration_filename)
    camera_matrix = calibration["camera_matrix"]
    dist_coefs = calibration["dist_coefs"]

    return camera_matrix, dist_coefs

def extract_marker_position(corners, marker_lenght, camera_matrix, dist_coefs):
    # Extract the pose of the marker
    rvec, tvec, _ = cv2.aruco.estimatePoseSingleMarkers(corners, marker_lenght, camera_matrix, dist_coefs)

    # Convert the rotation vector to a rotation matrix
    R, _ = cv2.Rodrigues(rvec)

    # Extract the position of the marker
    position = -np.matrix(R).T * np.matrix(tvec)
    
    return position

def ids_distances_and_angles_list(image, camera_matrix, dist_coefs):
    # Convert the image to grayscale
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    # Detect the markers in the image
    corners, ids, _ = cv2.aruco.detectMarkers(gray, aruco_dict)

    # Initialize a dictionary to store the distances and angles for each marker
    ids_distances_and_angles = {}

    # Iterate over each detected marker
    for i, marker_id in enumerate(ids):
        # Extract the position
        position = extract_marker_position(corners, marker_lenght, camera_matrix, dist_coefs)

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
        position = extract_marker_position(marker_lenght, camera_matrix, dist_coefs)

        # Calculate the distance and angle to the marker
        distance = np.linalg.norm(position)
        angle = np.arctan2(position[1], position[0])

        x_pos, y_pos = calculate_xy_distance(distance, angle)

        # Store the distance and angle in the dictionary
        ids_x_pos_y_pos[i] = (marker_id, x_pos, y_pos)

    return ids_distances_and_angles

def commands_to_nearest_marker(frame, calibration_filename, marker_lenght):

    camera_matrix, dist_coefs = get_calibration_parameters_from_file(calibration_filename)
    # Convert the image to grayscale
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    # Detect the markers in the image
    corners, ids, _ = cv2.aruco.detectMarkers(gray, aruco_dict)

    # Initialize a dictionary to store the distance and angle for each marker ID
    distances_and_angles = {}
    for i, marker_id in enumerate(ids):
        # Extract the position of the marker
        position = extract_marker_position(marker_length, camera_matrix, dist_coefs)

        # Calculate the distance and angle to the marker
        distance = np.linalg.norm(position)
        angle = np.arctan2(position[1], position[0])

        # Store the distance and angle for the marker ID in the dictionary
        distances_and_angles[marker_id] = (distance, angle)

    # Find the marker ID with the minimum distance
    nearest_marker_id = min(distances_and_angles, key=lambda x: distances_and_angles[x][0])

    # Get the distance and angle for the nearest marker
    nearest_marker_distance = distances_and_angles[nearest_marker_id][0]
    nearest_marker_angle = distances_and_angles[nearest_marker_id][1]

    # Calculate the x and y distance to the nearest marker
    x_distance, y_distance = calculate_xy_distance(nearest_marker_distance, nearest_marker_angle)

    commands = create_command_str(x_distance, y_distance)

    # Print the list of commands
    return commands

def send_commands(commands):
    print("Sending commands")
    # TODO
    print(commands)

def main():

    default_calibration_filename = "calibration.npz"
    camera_index = 1
    marker_lenght = 0.15

    # Create a VideoCapture object
    cam = cv2.VideoCapture(camera_index)
    print("Camera is open")

    if not os.path.exists(default_calibration_filename):
        calibration_filename = camera_calibration()
    else:
        calibration_filename = default_calibration_filename

    while(cam.isOpened()):
        # Read the frame from the webcam
        ret, frame = cam.read()

        commands = commands_to_nearest_marker(frame, calibration_filename, marker_lenght)
        if bool(my_list):
            send_commands(commands)

if __name__ == "__main__":
    
    # main()
    get_calibration_parameters_from_file("calibration.npz")
