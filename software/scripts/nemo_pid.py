from PIL import Image, ImageTk
from matplotlib import animation
import cv2
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import tkinter as tk
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.animation as animation

fig, ax = plt.subplots(2, 2, figsize=(10, 8))


def update_graph(ax):
    df = pd.read_csv("output.csv")

    ax[0, 0].clear()
    ax[0, 0].plot(df['vl'])
    ax[0, 0].set_title('vl')

    ax[0, 1].clear()
    ax[0, 1].plot(df['pl'])
    ax[0, 1].set_title('pl')

    ax[1, 0].clear()
    ax[1, 0].plot(df['vr'])
    ax[1, 0].set_title('vr')

    ax[1, 1].clear()
    ax[1, 1].plot(df['pr'])
    ax[1, 1].set_title('pr')


ani = animation.FuncAnimation(fig, update_graph, interval=1000)

plt.tight_layout()
plt.show()


class Application(tk.Frame):
    def __init__(self, master=None):
        super().__init__(master)
        self.master = master
        self.pack()
        self.create_widgets()

    def create_widgets(self):
        self.close_button = tk.Button(
            self, text="Close", command=self.master.quit)
        self.close_button.grid(row=9, column=0, pady=10, sticky="w")

        self.left_pid_kp_label = tk.Label(self, text="Left Kp")
        self.left_pid_kp_label.grid(row=1, column=0, sticky="e")
        self.left_pid_kp_entry = tk.Entry(self)
        self.left_pid_kp_entry.grid(row=1, column=1, sticky="w")

        self.left_pid_ki_label = tk.Label(self, text="Left Ki")
        self.left_pid_ki_label.grid(row=2, column=0, sticky="e")
        self.left_pid_ki_entry = tk.Entry(self)
        self.left_pid_ki_entry.grid(row=2, column=1, sticky="w")

        self.left_pid_kd_label = tk.Label(self, text="Left Kd")
        self.left_pid_kd_label.grid(row=3, column=0, sticky="e")
        self.left_pid_kd_entry = tk.Entry(self)
        self.left_pid_kd_entry.grid(row=3, column=1, sticky="w")

        self.right_pid_kp_label = tk.Label(self, text="Right Kp")
        self.right_pid_kp_label.grid(row=4, column=0, sticky="e")
        self.right_pid_kp_entry = tk.Entry(self)
        self.right_pid_kp_entry.grid(row=4, column=1, sticky="w")

        self.right_pid_ki_label = tk.Label(self, text="Right Ki")
        self.right_pid_ki_label.grid(row=5, column=0, sticky="e")
        self.right_pid_ki_entry = tk.Entry(self)
        self.right_pid_ki_entry.grid(row=5, column=1, sticky="w")

        self.right_pid_kd_label = tk.Label(self, text="Right Kd")
        self.right_pid_kd_label.grid(row=6, column=0, sticky="e")
        self.right_pid_kd_entry = tk.Entry(self)
        self.right_pid_kd_entry.grid(row=6, column=1, sticky="w")

        self.update_left_pid_button = tk.Button(
            self, text="Update left PID", command=self.interact_with_robot)
        self.update_left_pid_button.grid(
            row=7, column=0, columnspan=2, pady=10, sticky="w")

        self.update_right_pid_button = tk.Button(
            self, text="Update Right PID", command=self.interact_with_robot)
        self.update_right_pid_button.grid(
            row=8, column=0, columnspan=2, pady=10, sticky="w")

    def interact_with_robot(self):
        print("Interacting with robot")

        kp = self.pid_entry_1.get()
        ki = self.pid_entry_2.get()
        kd = self.pid_entry_3.get()

    def update_graph(self):
        update_graph(self.ax)

    def start(self):
        self.update_camera()
        self.ani = animation.FuncAnimation(
            self.fig_canvas.figure, self.update_graph, interval=1000)
        self.mainloop()


root = tk.Tk()
app = Application(master=root)
app.start()
