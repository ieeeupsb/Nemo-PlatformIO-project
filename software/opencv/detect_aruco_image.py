import cv2
import cv2.aruco as aruco
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.image as mpimg

# Load the marker image
img = cv2.imread("marker.jpg")


# Convert the image to grayscale
img_rgb = cv2.cvtColor(img, cv2.COLOR_XYZ2BGR)
print(img.shape)
gray = img_gray = rgb2gray(img_rgb)

print(img.shape[2])
# Load the dictionary that was used to generate the marker
aruco_dict = aruco.Dictionary_get(aruco.DICT_4X4_50)

# Detect the marker in the image
parameters = aruco.DetectorParameters_create()
corners, ids, rejectedImgPoints = aruco.detectMarkers(
    gray, aruco_dict, parameters=parameters)

print(ids)

# Make sure that a marker was detected
if ids is not None and len(ids) > 0:
    # Print the identifier of the detected marker
    print(ids)

    # Draw the marker on the image
    img = aruco.drawDetectedMarkers(img, corners, ids)

# Show the image
cv2.imshow("Image", img)
cv2.waitKey(0)
cv2.destroyAllWindows()
