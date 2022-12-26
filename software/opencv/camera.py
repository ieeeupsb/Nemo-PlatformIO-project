import cv2

class Camera:
    def __init__(self, index):
        self.index = index
    
    def set_parameters_from_file(self, filename):
        calibration = np.load(filename)
        self.camera_matrix = calibration["camera_matrix"]
        self.dist_coefs = calibration["dist_coefs"]

    def __init__(self, index, parameters_filename):
        self.index = index
        set_parameters_from_file(parameters_filename):

    def start(self):
        # Create a VideoCapture object
        cam = cv2.VideoCapture(self.index)
        print("Camera is open")