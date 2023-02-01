import pygame
import paramiko
import serial
import time


def serial_channel_over_ssh(host, port, username, password, serial_port):
    ssh = paramiko.SSHClient()
    ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    ssh.connect(host, port, username, password)

    # Open a channel to the serial port
    channel = ssh.get_transport().open_session()
    channel.get_pty()
    channel.exec_command("screen %s 9600" % serial_port)

    return channel


def send_command(channel, command):
    ser.write(command.encode())
    print("Sending commmand" + command)
    # try:
    #     if channel.active:
    #         # print(command)
    #         channel.send(command + "\r")
    #         while True:
    #             if channel.recv_ready():
    #                 output = channel.recv(1024).decode("utf-8")
    #                 print(output)
    #                 break
    #             if channel.exit_status_ready():
    #                 break
    #     else:
    #         print("The channel is not active. Cannot send command.")
    # except OSError as e:
    #     print("Error sending command: ", e)


def send_coordinates(x, y, channel):
    # ser.write(("%.2f,%.2f" % (x, y)).encode())
    coordinates_string = "%.2f,%.2f" % (x, y)
    print("Your coordinates were sent and the robot was started: (%.2f, %.2f)\n")
    send_command(coordinates_string, channel)


def send_joystick_command(x, y, channel):

    joystick_command_string = "v:" + str(x*10) + ";w:" + str(y*10)

    send_command(channel, joystick_command_string)


def stop_robot(channel):
    send_command(channel, "stop")


def start_robot(channel):
    send_command(channel, "start")


# Initialize pygame and joystick
pygame.init()
pygame.joystick.init()
joystick = pygame.joystick.Joystick(0)
joystick.init()
start = False

ser = serial.Serial('/dev/ttyACM0')  # open serial port
# this would depend on the protocol for the USB device

# Replace 'ttyACM0' with your actual serial port
# ser = serial.Serial('/dev/ttyACM0', 9600)
channel = 0


while True:
    pygame.event.get()
    x_axis = joystick.get_axis(1)
    y_axis = joystick.get_axis(3)
    x = -int(x_axis * 10)
    y = -int(y_axis * 10)

    if start == True:
        send_joystick_command(x, y, channel)

    buttons = joystick.get_numbuttons()
    for i in range(buttons):
        button = joystick.get_button(i)
        if button == 1:
            if i == 0:
                start_robot(channel)
                start = True
            elif i == 1:
                stop_robot(channel)
                start = False
    time.sleep(0.75)


pygame.quit()
ssh.close()
ser.close()
