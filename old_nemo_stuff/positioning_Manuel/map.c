#include "map.h"
#include <stdlib.h>

int map_array[7][9] = {     {I0, I1, I2, I3, XX, XX, XX, XX, XX},
                            { 5,  6,  7,  8,  9, LL, LL, LL, 10},
                            {LL, XX, XX, XX, 11, B0, B1, LL, 14},
                            {14, LL, A0, A1, 17, B2, B3, LL, 14},
                            {21, LL, A2, A3, 24, XX, XX, XX, 14},
                            {ST, LL, LL, LL, 26, 27, 28, 29, 30},
                            {XX, XX, XX, XX, XX, O0, O1, O2, O3}
}; 