#include "mode_main.h"
#include "motion.h"

Motion motion_g;

int main_function() {

    motion_g.test_motors();
    motion_g.test_encoders();

    return 0;
}
