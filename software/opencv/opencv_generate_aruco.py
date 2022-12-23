import cv2
import cv2.aruco as aruco

# Set the desired marker size
marker_size = 200

# Create the marker image
marker_image = aruco.drawMarker(
    aruco.Dictionary_get(aruco.DICT_4X4_50),  # Use the 4x4_50 dictionary
    0,  # Use the first marker in the dictionary
    marker_size  # Set the marker size
)

# Save the marker image to a file
cv2.imwrite("marker.png", marker_image)

# Show the marker image
cv2.imshow("Marker", marker_image)
cv2.waitKey(0)
cv2.destroyAllWindows()
