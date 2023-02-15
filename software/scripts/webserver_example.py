import cv2
import numpy as np
import csv
import serial
from flask import Flask, Response

app = Flask(__name__)

# Define the video stream

# Define the serial port for communicating with the robot
serial_port = "/dev/ttyUSB0"  # change this to your serial port


def send_command(ser, command):
    ser.write(command.encode())
    print("Sending commmand: " + command)


def create_command(x, y, v, w):
    return "x:" + str(x) + ";y:" + str(y) + ";v:"+str(v) + ";w:" + str(w)


def create_speed_command(v, w):
    create_command(0, 0, v*3846, w*3846)


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


def follow_line(frame):
    linear_speed = 0.2

    # low_b = np.uint8([5, 5, 5])
    # high_b = np.uint8([0, 0, 0])
    # mask = cv2.inRange(frame, high_b, low_b)
    # contours, hierarchy = cv2.findContours(mask, 1, cv2.CHAIN_APPROX_NONE)
    # if len(contours) > 0:
    #     c = max(contours, key=cv2.contourArea)
    #     M = cv2.moments(c)
    #     if M["m00"] != 0:
    #         cx = int(M['m10']/M['m00'])
    #         cy = int(M['m01']/M['m00'])
    #         print("CX : "+str(cx)+"  CY : "+str(cy))
    #         if cx >= 120:
    #             print("Turn Left")
    #             command = create_speed_command(linear_speed, -0.2)
    #         if cx < 120 and cx > 40:
    #             print("On Track!")
    #             command = create_speed_command(linear_speed, 0)

    #         if cx <= 40:
    #             print("Turn Right")
    #             command = create_speed_command(linear_speed, 0.2)

    #         cv2.circle(frame, (cx, cy), 5, (255, 255, 255), -1)
    # else:
    #     print("I don't see the line")
    #     command = create_command(0, 0, 0, 0)

    command = create_command(0, 0, linear_speed, 0)

    return command


def generate():
    # while True:
    #     # Read a frame from the video stream
    #     ret, frame = cap.read()

    #     # Process the frame and send a command to the robot
    #     command = follow_line(frame)

    #     # Send the command to the robot over serial
    #     # send_command(serial_port, command)

    #     # Convert the frame to a JPEG image
    #     ret, jpeg = cv2.imencode('.jpg', frame)

    #     # Yield the JPEG image as a byte string
    #     yield (b'--frame\r\n'
    #            b'Content-Type: image/jpeg\r\n\r\n' + jpeg.tobytes() + b'\r\n')
    cap = cv2.VideoCapture(0)
    ser = serial.Serial(port='/dev/ttyACM0', baudrate=115200)

    command = create_command(1, 0.1, 1, 0)
    send_command(ser, command)
    command = create_command(2, 0.1, 1, 0)
    send_command(ser, command)

    while True:
        success, frame = cap.read()
        if not success:
            break
        else:
            command = follow_line(frame)
            send_command(ser, command)
            ret, buffer = cv2.imencode('.jpg', frame)
            frame = buffer.tobytes()
            yield (b'--frame\r\n'
                   b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')

    # Define the route to stream the video


@app.route('/video_feed')
def video_feed():
    return Response(generate(),
                    mimetype='multipart/x-mixed-replace; boundary=frame')


# Run the web application
if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)
