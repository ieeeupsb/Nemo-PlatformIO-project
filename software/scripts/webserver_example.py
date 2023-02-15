import cv2
import numpy as np
import csv
import serial
from flask import Flask, Response
import time
import threading
import queue

app = Flask(__name__)

# Define the video stream

# Define the serial port for communicating with the robot
serial_port = "/dev/ttyUSB0"  # change this to your serial port


def send_command(ser, command):
    ser.write(command.encode())
    print("Sending commmand: " + command)


def send_command_with_interval(ser, command, interval):
    def send_command_helper():
        while True:
            send_command(ser, command)
            time.sleep(interval)

    thread = threading.Thread(target=send_command_helper)
    thread.start()
    return thread


def create_command(x, y, v, w):
    return "x:" + str(x) + ";y:" + str(y) + ";v:"+str(v) + ";w:" + str(w)


def create_speed_command(v, w):
    return create_command(0, 0, v*3846, w*3846)


def write_values_to_csv(line):
    values = line.split(",")

    if len(values) == 4:
        vl, pl, vr, pr = values
        vl = float(vl)/1000
        pl = int(pl)
        vr = float(vr)/1000
        pr = int(pr)

        values = vl, pl, vr, pr

        # Write the values to a CSV file
        with open("output.csv", "a") as csvfile:
            writer = csv.writer(csvfile)
            writer.writerow(values)


ser = serial.Serial(port='/dev/ttyACM0', baudrate=115200)
cap = cv2.VideoCapture(0)

frame_queue = queue.Queue()  # Create a queue to hold frames
command_queue = queue.Queue()  # Create a queue to hold frames


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

    return command


def read_frames():
    while True:
        success, frame = cap.read()
        if success:
            last_frame = frame

        frame_queue.put(last_frame)  # Put the new frame in the queue
        command = follow_line(last_frame)
        command_queue.put(command)
        # time.sleep(0.020)


def follow_line_and_send_command():
    while True:
        command = command_queue.get()
        if command is not None:
            send_command(ser, command_queue.get())
        time.sleep(2)
        print("sending commands\n\n\n\n")


# Run the web application
if __name__ == '__main__':

    time.sleep(1)
    command = create_command(1, 0.1, 1, 0)
    send_command(ser, command)
    time.sleep(1)
    command = create_command(2, 0.1, 1, 0)
    send_command(ser, command)
    time.sleep(1)

    # # Create the two threads
    # generate_commands_thread = threading.Thread(target=read_frames)
    # send_commands_thread = threading.Thread(
    #     target=follow_line_and_send_command)

    # # Start the threads
    # generate_commands_thread.start()
    # send_commands_thread.start()

    # # Wait for the threads to finish (which they never will, because they run indefinitely)
    # generate_commands_thread.join()
    # send_commands_thread.join()

    while True:
        success, frame = cap.read()
        if success:
            last_frame = frame

        frame_queue.put(last_frame)  # Put the new frame in the queue
        command = follow_line(last_frame)
        send_command(command)
