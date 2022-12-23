import serial
import time

# Set up the serial connection
ser = serial.Serial('/dev/ttyACM0', baudrate=15200)

# Define the command to send to the Pico
# Continuously send the command
while True:
    ser.write(b'<DIR:LEFT;DIST:0.5;SPEED:0.5>')
    time.sleep(0.5)

# Send the command over the serial connection
ser.write(command.encode())

# Close the serial connection
ser.close()
