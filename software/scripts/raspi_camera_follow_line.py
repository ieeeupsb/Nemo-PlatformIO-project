import numpy as np
import cv2
from picamera.array import PiRGBArray
from picamera import PiCamera
import time
from nemo_commands import send_command, create_command, create_speed_command


def follow_line(frame):
    linear_speed = 0.2
    max_angular_speed = 0.2
    command = create_command(0, 0, 0, 0)

    low_b = np.uint8([5, 5, 5])
    high_b = np.uint8([0, 0, 0])
    mask = cv2.inRange(frame, high_b, low_b)
    contours, hierarchy = cv2.findContours(mask, 1, cv2.CHAIN_APPROX_NONE)

    if len(contours) > 0:
        c = max(contours, key=cv2.contourArea)
        M = cv2.moments(c)
        if M["m00"] != 0:
            cx = int(M['m10']/M['m00'])
            cy = int(M['m01']/M['m00'])

            center_x = frame.shape[1] // 2
            error = cx - center_x
            angular_speed = error / center_x * max_angular_speed

            command = create_speed_command(linear_speed, angular_speed)

            print("linear speed" + str(linear_speed) +
                  " angular speed" + str(angular_speed))

    print("no line")

    return command


ser = serial.Serial(port='/dev/ttyACM0', baudrate=115200)
cap = cv2.VideoCapture(-2)

if __name__ == '__main__':

    time.sleep(1)
    command = create_command(1, 0.1, 1, 0)
    send_command(ser, command)
    time.sleep(1)
    command = create_command(2, 0.1, 1, 0)
    send_command(ser, command)
    time.sleep(1)

    # Initialize the camera and grab a reference to the raw camera capture
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.framerate = 32
    rawCapture = PiRGBArray(camera, size=(640, 480))

    # Allow the camera to warm up
    time.sleep(0.1)

    # Capture frames from the camera
    for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
        # Get the raw NumPy array representing the image
        image = frame.array

        # Convert the image to grayscale
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        command = follow_line(frame)
        send_command(ser, command)
