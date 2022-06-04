#ifndef MIGUEL_HELP_H
#define MIGUEL_HELP_H

#define FOWARD 1
#define BACKWARDS 0

#define CORRECT_TO_RIGHT 4 // NEED TO TURN RIGHT
#define CORRECT_TO_LEFT 16 // NEED TO TURN LEFT
#define RIGHT_CURVE 144
#define LEFT_CURVE 12
#define INTERCEPTION 156
#define LINE 132
#define FREE 0

// Well, just for debugging, either Wifi, Serial or printf
void debug_message(const char *message);

// Rotates with two modes, box attached(1) and box not attached(0)
// if degree positive, rotates to the right, if negative, rotates to the left
void rotate(int degrees, int boxAttached);

// walks until intersection
// ao recuar, onde deteta a interseçao, doesnt really matter
void walk(int millimeters, int direction, int turn);

void eletromagnet_on();

void eletromagnet_off();

/*
return 0 - not av
return 1 - box av
*/
int box_availabe();

/*c possible values in .h file
choose the value you want to be returned for testing
in facton this fucnti is a macro:
    #define LINE_CASE_FASTheck GPIO.in1.val & 0x9C // GPIO.in1.val & 0x9C =
L200L1 L4L300
*/
int LINE_CASE_FAST(int what_miguel_wants_to_be_returned);

// new functions added that Manuel doesnt know exist, or exist, but MIguel just
// added more

void wait(int milis);

#endif