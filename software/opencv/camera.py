import cv2
import pickle
import sys
import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle


class ArucoMarker:
    def __init__(self, dictionary, corners, id, length):
        self.dictionary = dictionary
        self.corners = corners
        self.id = id
        self.length = length


class Camera:

    def set_parameters_from_file(self, parameters_filename):
        try:
            with open(parameters_filename, 'rb') as f:
                data = pickle.load(f)
        except FileNotFoundError:
            print("The file " + parameters_filename + " was not found.")
            sys.exit(1)

        self.cameraMatrix, self.distCoeffs, self.rvecs, self.tvecs = data

    def __init__(self, index, parameters_filename):
        self.index = index
        self.set_parameters_from_file(parameters_filename)
        self.cv2_cam = None  # Add this line to define the cv2_cam attribute

    def start(self):
        # Create a VideoCapture object
        self.cv2_cam = cv2.VideoCapture(self.index)
        print("Camera is open")

    def isOpened(self):
        try:
            return self.cv2_cam.isOpened()

        except AttributeError:
            self.start()
            return self.cv2_cam.isOpened()

    def read(self):
        return self.cv2_cam.read()

    def detectMarkers(self, aruco_dict):
        ret, frame = self.cv2_cam.read()
        # Convert the image to grayscale
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        cv2.imshow("Camera Output", frame)

        # Detect the markers in the image
        return cv2.aruco.detectMarkers(gray, aruco_dict)

    def estimatePoseSingleMarkers(self, corners, marker_size):

        return cv2.aruco.estimatePoseSingleMarkers(
            corners, marker_size, self.cameraMatrix, self.distCoeffs)


class ArucoMap:
    def __init__(self, x_min=0, x_max=2, y_min=0, y_max=2):
        self.x_min, self.x_max = x_min, x_max
        self.y_min, self.y_max = y_min, y_max

        fig, ax = plt.subplots()
        self.fig = fig
        self.ax = ax
        self.ax.set_xlim(x_min, x_max)
        self.ax.set_ylim(y_min, y_max)
        self.ax.set_aspect("equal")

        self.added_markers = set()  # set to store added markers

    def addMarker(self, marker, x_pos, y_pos):
        if x_pos < self.x_min or x_pos > self.x_max or y_pos < self.y_min or y_pos > self.y_max:
            print("Marker is out of bounds!")
            return

        # Check if marker has already been added
        for m in self.added_markers:
            if m.id == marker.id:
                print("Marker with ID {} has already been added!".format(m.id))
                return

        # Add marker ID to set of added marker IDs
        self.added_markers.add(marker)

        # Add a scatter plot and a text label to the axis
        text_x = x_pos - marker.length/2
        text_y = y_pos + marker.length/2
        text_string = "Marker " + str(marker.id)
        self.ax.text(text_x, text_y, text_string)

        # Add a rectangle patch to the axis
        self.ax.add_patch(Rectangle((x_pos - marker.length/2, y_pos -
                          marker.length/2), marker.length, marker.length, fill=False))

    def show(self):
        plt.show()

    def save(self, filename):
        with open(filename, "wb") as f:
            pickle.dump(self.fig, f)

    def load(self, filename):
        with open(filename, "wb") as f:
            self.fig = pickle.load(f)

    def toImage(self, filename):
        self.fig.savefig(filename, format="jpg")
