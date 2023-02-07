import cv2
import serial
import numpy as np


def send_command(command):
    ser.write(command.encode())
    print("Sending commmand: " + command)


def create_command(x, y, v, w):
    return "x:" + str(x) + ";y:" + str(y) + ";v:"+str(v) + ";w:" + str(w)


ser = serial.Serial('/dev/ttyACM0')
cap = cv2.VideoCapture(0)
cap.set(3, 160)
cap.set(4, 120)

while True:
    ret, frame = cap.read()
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
            print("CX : "+str(cx)+"  CY : "+str(cy))
            if cx >= 120:
                print("Turn Left")
                command = create_command(0, 0, 0.2, 0.4)
            if cx < 120 and cx > 40:
                print("On Track!")
                command = create_command(0, 0, 0.4, 0)
            if cx <= 40:
                print("Turn Right")
                command = create_command(0, 0, 0.4, 0.2)
            cv2.circle(frame, (cx, cy), 5, (255, 255, 255), -1)
    else:
        print("I don't see the line")
        command = create_command(0, 0, 0, 0)

    send_command(command)

    cv2.drawContours(frame, c, -1, (0, 255, 0), 1)
    cv2.imshow("Mask", mask)
    cv2.imshow("Frame", frame)

    if cv2.waitKey(1) & 0xff == ord('q'):   # 1 is the time in ms
        command = create_command(0, 0, 0, 0)
        break
cap.release()
cv2.destroyAllWindows()
