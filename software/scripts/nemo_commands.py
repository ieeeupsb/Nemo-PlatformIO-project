# Define the serial port for communicating with the robot
serial_port = "/dev/ttyACM0"  # change this to your serial port


def send_command(ser, command):
    ser.write(command.encode())
    print("Sending commmand: " + command)


def create_command(x, y, v, w):
    return "x:" + str(x) + ";y:" + str(y) + ";v:"+str(v) + ";w:" + str(w)


def create_speed_command(v, w):
    return create_command(0, 0, v*3846, w*3846)
