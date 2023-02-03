import numpy
import cv2
import cv2.aruco as aruco


# Constant parameters used in Aruco methods
ARUCO_PARAMETERS = aruco.DetectorParameters_create()
ARUCO_DICT = aruco.Dictionary_get(aruco.DICT_6X6_1000)

# Create grid board object we're using in our stream
board = aruco.GridBoard_create(
    markersX=2,
    markersY=2,
    markerLength=0.09,
    markerSeparation=0.01,
    dictionary=ARUCO_DICT)

# Create vectors we'll be using for rotations and translations for postures
rvecs, tvecs = None, None

cam = cv2.VideoCapture(0)

print("cam is open")


while (cam.isOpened()):
    # Capturing each frame of our video stream
    # Load the image containing the marker
    image = cv2.imread("marker.jpg")
    cam = cv2.VideoCapture(1)

    print("cam is open")

    # Convert the image to grayscale
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    # Set up the dictionary of ARUCO markers
    aruco_dict = cv2.aruco.Dictionary_get(cv2.aruco.DICT_4X4_50)

    # Detect the markers in the image
    corners, ids, _ = cv2.aruco.detectMarkers(gray, aruco_dict)

    # Extract the pose of the first marker
    rvec, tvec, _ = cv2.aruco.estimatePoseSingleMarkers(
        corners[0], 0.05, camera_matrix, dist_coefs)

    # Convert the rotation vector to a rotation matrix
    R, _ = cv2.Rodrigues(rvec)

    # Extract the position of the marker
    position = -np.matrix(R).T * np.matrix(tvec)

    # Extract the orientation of the marker
    euler_angles = cv2.decomposeProjectionMatrix(np.hstack((R, tvec)))[6]

    # Print the position and orientation of the marker
    print("Position:", position)
    print("Orientation:", euler_angles)

    # The following code is used to watch a video stream, detect Aruco markers, and use
    # a set of markers to determine the posture of the camera in relation to the plane
    # of markers.
    #
    # Assumes that all markers are on the same plane, for example on the same piece of paper
    #
    # Requires camera calibration (see the rest of the project for example calibration)

    cv2.destroyAllWindows()
