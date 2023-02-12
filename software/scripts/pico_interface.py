import pygame
import time
import serial

canSend = False
def usleep(x): return time.sleep(x/1000000.0)


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


def constrain(value, lower_bound, upper_bound):
    return max(lower_bound, min(value, upper_bound))


ser = serial.Serial(port='/dev/ttyACM0', baudrate=115200)

menu_trigger_key = "m"
trajectory_trigger_key = "t"
print("Press 'm' to open the menu")


controller_is_connected = check_controller()

if controller_is_connected:
    pygame.init()
    pygame.joystick.init()
    joystick = pygame.joystick.Joystick(0)
    joystick.init()

    v = 0
    w = 0

    number_of_gears = 3
    gear = 3
    absolute_max_speed = 0.3

    while True:
        pygame.event.get()
        x_axis = joystick.get_axis(1)
        y_axis = joystick.get_axis(3)

        if joystick.get_button(1):
            print("aug gear")
            gear = gear + 1
        elif joystick.get_button(2):
            print("reduce gear")
            gear = gear - 1

        print(gear)
        constrain(gear, -1, number_of_gears)

        if gear == 0:
            increment = 0
        else:
            gear_max_speed = absolute_max_speed / (number_of_gears / gear)
            print("gear max speed:" + str(gear_max_speed))
            increment = -round(x_axis, 1)*(1/gear)
            print("increment:" + str(increment))

        y_axis = -round(y_axis, 1)

        if increment != 0:
            v = v + increment
        else:
            v = v/2

        v = constrain(v, -0.3, gear_max_speed)
        v = round(v, 2)

        send_command(create_command(0, 0, v, w))

        if not ser.in_waiting:  # Or: while ser.inWaiting():
            line = ser.readline()
            # print(line)
        time.sleep(0.000001)


while True:
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
    else:
        canSend = False

    if canSend:
        send_command(command_to_send)

    # elif ser.in_waiting:
    line = ser.readline()
    print(line)
    # canSend = True


pygame.quit()
ssh.close()
ser.close()
