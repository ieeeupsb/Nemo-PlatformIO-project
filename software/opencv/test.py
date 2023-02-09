import numpy as np
import cv2

# Load the video capture object
cap = cv2.VideoCapture(0)

# Check if camera is opened
if not cap.isOpened():
    raise Exception("Could not open video device")

# Set the target line color in HSV color space
lower_color = np.array([40, 70, 70])
upper_color = np.array([60, 255, 255])

# Set the linear and angular speeds
linear_speed = 0.1
angular_speed = 0.1

while True:
    # Capture a frame
    ret, frame = cap.read()
    if not ret:
        break

    # Convert the frame to HSV color space
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # Threshold the frame based on the target color
    mask = cv2.inRange(hsv, lower_color, upper_color)

    # Find the contours in the thresholded image
    _, contours, _ = cv2.findContours(
        mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

    # Find the largest contour
    largest_contour = None
    largest_area = 0
    for contour in contours:
        area = cv2.contourArea(contour)
        if area > largest_area:
            largest_area = area
            largest_contour = contour

    # Find the center of the largest contour
    if largest_contour is not None:
        M = cv2.moments(largest_contour)
        if M["m00"] != 0:
            cx = int(M["m10"] / M["m00"])
            cy = int(M["m01"] / M["m00"])

            # Calculate the error
            error = cx - frame.shape[1] // 2

            # Set the angular speed based on the error
            angular_speed = -error * 0.01

    # Send the linear and angular speeds to the robot
    # send_speed_command(linear_speed, angular_speed)

# Release the video capture object
cap.release()

# Close all windows
cv2.destroyAllWindows()
