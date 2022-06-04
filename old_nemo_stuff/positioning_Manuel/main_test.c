#include <stdio.h>
#include "miguel_help.h"

#define FOWARD 1
#define BACKWARDS 0

#define ST 0
#define I0 1
#define I1 2
#define I2 3
#define I3 4
#define O0 5
#define O1 6
#define O2 7
#define O3 8
#define B0 9
#define B1 10
#define A0 11
#define A1 12


void move(int origem, int destino) {
    switch (origem) {
        case ST:
            debug_message("moving to I0");
            return;
        case I0:
            switch (destino) {
                case O0:
                    debug_message("moving to O0");
                    return;
                case A0:
                    debug_message("moving to A0");
                    return;
                case B0:
                    debug_message("moving to B0");
                    return;
                default:
                    debug_message("Error in move function");
                    return;
            }
        case I1:
            switch (destino) {
                case O1:
                    debug_message("moving to O1");
                    return;
                case A0:
                    debug_message("moving to A0");
                    return;
                case B0:
                    debug_message("moving to B0");
                    return;
                default:
                    debug_message("Error in move function");
                    return;
            }
        case I2:
            switch (destino) {
                case O2:
                    debug_message("moving to O2");
                    return;
                case A0:
                    debug_message("moving to A0");
                    return;
                case B0:
                    debug_message("moving to B0");
                    return;
                default:
                    debug_message("Error in move function");
                    return;
            }
        case I3:
            switch (destino) {
                case O3:
                    debug_message("moving to O3");
                    return;
                case A0:
                    debug_message("moving to A0");
                    return;
                case B0:
                    debug_message("moving to B0");
                    return;
                default:
                    debug_message("Error in move function");
                    return;
            }
        case A0:
            debug_message("moving to A1");
            return;
        case A1:
            debug_message("moving to B0");
            return;
        case B0:
            debug_message("moving to B1");
            return;
        case B1:
            switch (destino) {
                case O0:
                    debug_message("moving to O0");
                    return;
                case O1:
                    debug_message("moving to O1");
                    return;
                case O2:
                    debug_message("moving to 02");
                    return;
                case O3:
                    debug_message("moving to 03");
                    return;
                default:
                    debug_message("Error in move function");
                    return;
            }        
        default:
            debug_message("Error in move function");
            return;
    }
}

int main() {
    int origem = 0;
    int destino = 2;
    move(origem, destino);
}