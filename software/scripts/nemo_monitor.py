import tkinter as tk
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import matplotlib.pyplot as plt
import cv2
import pandas as pd
from matplotlib import animation
from PIL import Image, ImageTk
import serial
import cv2
import numpy as np
import csv


def send_command(ser, command):
    ser.write(command.encode())
    print("Sending commmand: " + command)


def create_command(x, y, v, w):
    return "x:" + str(x) + ";y:" + str(y) + ";v:"+str(v) + ";w:" + str(w)


def send_speed_command(ser, v, w):
    send_command(ser, create_command(0, 0, v*3846, w*3846))


def follow_line(frame, serial):
    low_b = np.uint8([5, 5, 5])
    high_b = np.uint8([0, 0, 0])
    mask = cv2.inRange(high_b, low_b)
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

    command = create_command(0, 0, 1, 0)

    send_command(serial, command)


class Application(tk.Frame):
    def __init__(self, master=None):
        super().__init__(master)
        self.master = master
        self.pack()
        self.ser = serial.Serial(port='/dev/ttyACM0', baudrate=115200)

        values = "vl", "pl", "vr", "pr"

        with open("output.csv", "w") as csvfile:
            writer = csv.writer(csvfile)
            writer.writerow(values)
        self.create_widgets()
        command = create_command(1, 0.1, 1, 0)
        send_command(self.ser, command)
        command = create_command(2, 0.1, 1, 0)
        send_command(self.ser, command)

    def create_widgets(self):
        self.close_button = tk.Button(
            self, text="Close", command=self.master.quit)
        self.close_button.grid(row=2, column=1, pady=10, sticky="w")

        self.camera_label = tk.Label(self)
        self.camera_label.grid(row=0, column=1, sticky="nsew")
        self.grid_rowconfigure(0, weight=1)
        self.grid_columnconfigure(0, weight=1)

        fig, ax = plt.subplots(2, 2, figsize=(7, 8))

        self.fig_canvas = FigureCanvasTkAgg(fig, self)
        self.fig_canvas.get_tk_widget().grid(row=0, column=2, columnspan=3, sticky="w")

        self.cap = cv2.VideoCapture(0)
        self.ax = ax

        # left wheel buttons

        self.left_kp_entry = (tk.Entry(self))
        self.left_kp_entry.grid(row=4, column=2, pady=1, sticky="w")

        self.left_ki_entry = (tk.Entry(self))
        self.left_ki_entry.grid(row=4, column=3, pady=1, sticky="w")

        self.left_kd_entry = (tk.Entry(self))
        self.left_kd_entry.grid(row=4, column=4, pady=1, sticky="w")

        self.left_kd_button = tk.Button(
            self, text="Update left pid", command=self.update_left_pid)
        self.left_kd_button.grid(row=4, column=1, pady=1, sticky="w")

        # right wheel buttons

        self.right_kp_entry = (tk.Entry(self))
        self.right_kp_entry.grid(row=5, column=2, pady=1, sticky="w")

        self.right_ki_entry = (tk.Entry(self))
        self.right_ki_entry.grid(row=5, column=3, pady=1, sticky="w")

        self.right_kd_entry = (tk.Entry(self))
        self.right_kd_entry.grid(row=5, column=4, pady=1, sticky="w")

        self.right_kd_button = tk.Button(
            self, text="Update right pid", command=self.update_right_pid)
        self.right_kd_button.grid(row=5, column=1, pady=1, sticky="w")

    def update_left_pid(self):
        self
        command = create_command(1, float(self.left_kp_entry.get()),
                                 float(self.left_ki_entry.get()), float(self.left_kd_entry.get()))
        send_command(self.ser, command)

    def update_right_pid(self):
        self
        command = create_command(2, float(self.right_kp_entry.get()),
                                 float(self.right_ki_entry.get()), float(self.right_kd_entry.get()))
        send_command(self.ser, command)

    def update_camera(self):
        ret, frame = self.cap.read()
        self.frame = frame
        frame_going_to_image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        image = Image.fromarray(frame)
        image = ImageTk.PhotoImage(image)
        self.camera_label.configure(image=image)
        self.camera_label.image = image
        self.after(30, self.update_camera)

    def update_graph(self, num):
        df = pd.read_csv("output.csv")

        self.ax[0, 0].clear()
        self.ax[0, 0].plot(df['vl'])
        self.ax[0, 0].relim()
        self.ax[0, 0].autoscale_view()
        self.ax[0, 0].set_ylim([-3, 3])
        self.ax[0, 0].set_title('Left speed')

        self.ax[1, 0].clear()
        self.ax[1, 0].plot(df['pl'])
        self.ax[1, 0].set_title('pl')
        self.ax[1, 0].relim()
        self.ax[1, 0].autoscale_view()
        self.ax[1, 0].set_ylim([-5, 260])
        self.ax[1, 0].set_title('Left PWM')

        self.ax[0, 1].clear()
        self.ax[0, 1].plot(df['vr'])
        self.ax[0, 1].set_title('vr')
        self.ax[0, 1].relim()
        self.ax[0, 1].autoscale_view()
        self.ax[0, 1].set_ylim([-3, 3])
        self.ax[0, 1].set_title('Right speed')

        self.ax[1, 1].clear()
        self.ax[1, 1].plot(df['pr'])
        self.ax[1, 1].relim()
        self.ax[1, 1].autoscale_view()
        self.ax[1, 1].set_ylim([-5, 260])
        self.ax[1, 1].set_title('Right PWM')

        self.fig_canvas.draw()

    def main_program(self):
        # follow_line(self.frame, self.ser)

        if self.ser.in_waiting:
            line = self.ser.readline().strip().decode()
            # print(line)
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

    def start(self):
        self.update_camera()
        # self.ani = animation.FuncAnimation(
        #     self.fig_canvas.figure, self.update_graph, interval=30)
        # send command continuously every 1000 ms (1 second)
        self.after(30, self.main_program_continuously)
        self.mainloop()

    def main_program_continuously(self):
        self.main_program()
        # continue sending command every 1000 ms (1 second
        self.after(30, self.main_program_continuously)


root = tk.Tk()
app = Application(master=root)
app.start()
