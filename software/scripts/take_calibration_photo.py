import cv2

# Create a VideoCapture object
capture = cv2.VideoCapture(1)
# Set the number of photos to take
num_photos = 20

# Initialize a counter variable
i = 1

while i <= num_photos:
    # Read the frame from the webcam
    ret, frame = capture.read()

    # Save the frame to a file
    file_name = f"./camera-pic-of-charucoboard-{i}.jpg"
    cv2.imwrite(file_name, frame)

    # Increment the counter
    i += 1

# Release the VideoCapture object
capture.release()
