import serial
import paramiko
import pygame

canSend = False


def send_command(command):
    ser.write(command.encode())
    print("Sending commmand: " + command)


def create_command(x, y, v, w):
    return "x:" + str(x) + ";y:" + str(y) + ";v:"+str(v) + ";w:" + str(w)


coordinates_trigger_key = "c"


def open_menu():
    print("Press 'c' to select coordinates")
    print("Press 't' to select v and w")


def coordinates_menu():
    print("What x do you want to go:")
    x = input()
    print("What y do you want to go:")
    y = input()
    print("What v do you want to go:")
    v = input()
    w = 0

    return create_command(x, y, v, 0)


def trajectory_menu():

    print("What v do you want to go:")
    v = input()
    print("What w do you want to go:")
    w = input()

    return create_command(0, 0, v, w)


def check_controller():
    response = input("Is the controller connected (yes/no)? ")
    if response.lower() == "yes":
        controller_connected = True
        print("Controller connected")
        return True
    else:
        controller_connected = False
        print("Controller not connected")
        return False


ser = serial.Serial('/dev/ttyACM0')
menu_trigger_key = "m"
trajectory_trigger_key = "t"

print("Press 'm' to open the menu")
controller_is_connected = check_controller()

if controller_is_connected:
    pygame.init()
    pygame.joystick.init()
    joystick = pygame.joystick.Joystick(0)
    joystick.init()
    while True:
        pygame.event.get()
        x_axis = joystick.get_axis(1)
        y_axis = joystick.get_axis(3)
        x = -round(x_axis, 0) * 0.7
        y = -round(y_axis, 0) * 0.7
        command_to_send = create_command(0, 0, x, y)
        send_command(command_to_send)


while True:

    if controller_is_connected:
        pygame.event.get()
        x_axis = joystick.get_axis(1)
        y_axis = joystick.get_axis(3)
        x = -int(x_axis * 100)
        y = -int(y_axis * 100)
        command_to_send = create_command(0, 0, x, y)
        canSend = True
    elif not controller_is_connected:
        user_input = input()
        if user_input == menu_trigger_key:
            command_to_send = open_menu()
            canSend = False
        elif user_input == coordinates_trigger_key:
            command_to_send = coordinates_menu()
            canSend = True
        elif user_input == trajectory_trigger_key:
            command_to_send = trajectory_menu()
            canSend = True
        elif user_input == "1":
            command_to_send = create_command(1, 0, 0, 1)
            canSend = True
    else:
        canSend = False

    if canSend:
        send_command(command_to_send)

    elif ser.in_waiting:
        line = ser.readline()
        print(line)
    # canSend = True


pygame.quit()
ssh.close()
ser.close()
