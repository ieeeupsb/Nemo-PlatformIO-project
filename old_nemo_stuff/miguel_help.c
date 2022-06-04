#include "miguel_help.h"
#include "positioning.h"
#include <stdio.h>

void debug_message(const char *message)
{
	printf("%s", message);
}

void rotate(int degrees, int boxAttached)
{
	char auxs[21];
	sprintf(auxs, "Rotating %d degrees", degrees);
	debug_message(auxs);
}
/*
1- walk forward
0 - walk backwards
*/
// anda até detetar interseção num certo sitio
void walk(int millimeters, int direction, int turn)
{
	char auxs[32], help[32];
	sprintf(auxs, "Walking %d millimeters", millimeters);
	sprintf(help, "Walking backwards\n");
	debug_message(auxs);
	if (!direction)
		debug_message(help);
}

void eletromagnet_on()
{
	debug_message("Eletromagnet is on\n");
}

void eletromagnet_off()
{
	debug_message("Eletromagnet is off\n");
}
/*
return 0 - not av
return 1 - box av
*/
int box_availabe()
{
	debug_message("Box ava");
	return 1;
}
/*check possible values in .h file
choose the value you want to be returned for testing
in fact this fucntion is a macro:
	#define LINE_CASE_FAST GPIO.in1.val & 0x9C // GPIO.in1.val & 0x9C = L200L1 L4L300
*/
int LINE_CASE_FAST(int what_miguel_wants_to_be_returned)
{
	return what_miguel_wants_to_be_returned;
}

void wait(int milis)
{
	char aux[64];
	sprintf(aux, "Waited %d miliseconds\n", milis);
	debug_message(aux);
}
