import re
import serial

class MotionCommandComputer:

    pattern = r"<DIR:[A-Z]+;DIST:[0-9]+(\.[0-9]+)?;SPEED:[0-9]+(\.[0-9]+)?"
    
    def __init__(self, direction, distance, speed):
        self.direction = direction
        self.distance = distance
        self.speed = speed

    def send(serial_connection):

        sync_string = "<SYNC_RPI>"
        command_string = f"<DIR:{direction};DIST:{distance:.2f};SPEED:{speed:.2f}>"
        
        while "<SYNC_MCU>" != ser.readline().decode():
            serial_connection.write(sync_string.encode())
        
        while "<ACK>" != ser.readline().decode():
            serial_connection.write(command_string.encode())

    def receive(serial_connection):
        
        ack_string = "<ACK>"
        sync_string = "<SYNC_MCU>"
        receive_string = "EMPTY"
        
        while "<SYNC_RPI>" != ser.readline().decode():
            print("Wainting...")

        while not re.fullmatch(pattern, receive_string):
            serial_connection.write(sync_string.encode())

        serial_connection.write(ack_string.encode())

        print(receive_string)


def commands_list_to_go_to_coordinates(x, y):

    commands_list = []
    # Determine the direction of the movement
    if x < 0:
        direction = "LEFT"
    elif x > 0:
        direction = "RIGHT"

    distance = abs(x)
    speed = distance / 2  # Assume a speed of 0.5 units/second

    first_command = MotionCommandComputer(direction, distance, speed)
    commands_list.append(first_command)

    if y < 0:
        direction = "BACKWARD"
    elif y > 0:
        direction = "FOWARD"

    distance = abs(y)
    speed = distance / 2  # Assume a speed of 0.5 units/second

    second_command = MotionCommandComputer(direction, distance, speed)
    commands_list.append(second_command)
    
    return commands_list

serial_connection = serial.Serial('COM3', 9600)

first_command = MotionCommandComputer(direction, distance, speed)
first_command.send(serial_connection)
MotionCommandComputer.receive()