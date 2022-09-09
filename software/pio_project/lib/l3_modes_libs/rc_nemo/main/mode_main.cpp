#include "mode_main.h"
#include "motion.h"

Motion motion_g;

// TODO Fazer o Esqueleto do código para o controlo pela app bluetooth
int main_function() {
    // setup
    // while (main while)
    // [
    //     pedir os valores a app

    //     se available
    //         pwm_esquerdo_temp = incremento_esquerdo*multiplicador
    //         se pwm_esquerdo_temp dentro da RANGE
    //             pwm_esquerdo = pwm_esquerdo_temp
    //         senão
    //             continua
    //         ->mesma coisa para o direito
    //     senão
    //         continua

    // ]

    motion_g.test_motors();
    motion_g.test_encoders();

    return 0;
}
