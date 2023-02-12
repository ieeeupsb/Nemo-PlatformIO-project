import tkinter as tk
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import matplotlib.pyplot as plt
import cv2
import pandas as pd
from matplotlib import animation
from PIL import Image, ImageTk


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

        self.camera_label = tk.Label(self)
        self.camera_label.grid(row=0, column=0, sticky="nsew")
        self.grid_rowconfigure(0, weight=1)
        self.grid_columnconfigure(0, weight=1)

        fig, ax = plt.subplots(2, 2, figsize=(10, 8))

        self.fig_canvas = FigureCanvasTkAgg(fig, self)
        self.fig_canvas.get_tk_widget().grid(row=0, column=1, columnspan=2, sticky="nsew")

        self.cap = cv2.VideoCapture(0)
        self.ax = ax

    def update_camera(self):
        ret, frame = self.cap.read()
        frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        image = Image.fromarray(frame)
        image = ImageTk.PhotoImage(image)
        self.camera_label.configure(image=image)
        self.camera_label.image = image
        self.after(30, self.update_camera)

    def update_graph(self, num):
        df = pd.read_csv("output.csv")

        self.ax[0, 0].clear()
        self.ax[0, 0].plot(df['vl'])
        self.ax[0, 0].set_title('vl')

        self.ax[0, 1].clear()
        self.ax[0, 1].plot(df['pl'])
        self.ax[0, 1].set_title('pl')

        self.ax[1, 0].clear()
        self.ax[1, 0].plot(df['vr'])
        self.ax[1, 0].set_title('vr')

        self.ax[1, 1].clear()
        self.ax[1, 1].plot(df['pr'])
        self.ax[1, 1].set_title('pr')

        self.fig_canvas.draw()

    def start(self):
        self.update_camera()
        self.ani = animation.FuncAnimation(
            self.fig_canvas.figure, self.update_graph, interval=1000)
        self.mainloop()


root = tk.Tk()
app = Application(master=root)
app.start()
