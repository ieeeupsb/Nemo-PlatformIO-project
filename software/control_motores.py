import time

# def L_Speed(speed):
#     if speed <= 0:
#         GPIO.output(L_DIR_PIN, GPIO.HIGH)
#     else:
#         GPIO.output(L_DIR_PIN, GPIO.LOW)

#     speed = abs(speed)
#     if speed > 100:
#         speed = 100

#     L_MOTOR.ChangeDutyCycle(speed)


# def R_Speed(speed):
#     if speed <= 0:
#         GPIO.output(R_DIR_PIN, GPIO.LOW)
#     else:
#         GPIO.output(R_DIR_PIN, GPIO.HIGH)

#     speed = abs(speed)
#     if speed > 100:
#         speed = 100

#     R_MOTOR.ChangeDutyCycle(speed)


def Direction(difference):
    difference /= 2
    p_int.send_command(p_int.create_command(0, 0, 0, difference))


def BaseSpeed(speed):
    p_int.send_command(p_int.create_command(0, 0, speed, 0))


def GetSpeed():
    global SPEED
    return SPEED


def MotorsStop():
    L_MOTOR.stop()
    R_MOTOR.stop()
    GPIO.cleanup()
