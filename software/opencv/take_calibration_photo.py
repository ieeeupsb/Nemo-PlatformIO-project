import cv2

# Create a VideoCapture object
capture = cv2.VideoCapture(1)

# Read the frame from the webcam
ret, frame = capture.read()

# Save the frame to a file
cv2.imwrite("photo.jpg", frame)

# Release the VideoCapture object
capture.release()