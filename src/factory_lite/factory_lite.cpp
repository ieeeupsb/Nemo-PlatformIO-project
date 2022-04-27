#include "factory_lite.h"

#define MISSION 0 // Buscar/Deixar caixa
#define AROUND 1  // Move around the map

void factory_lite_setup() {
    if (DEBUG_MODE)
        Serial.begin(115200);

    wifi_setup(UDP_ADDRESS, UDP_PORT);
    motors_setup();
    sonar_setup();
    line_setup();
    eletromagnet_setup();
}

// serve para orientar para o sitio certo sempre que tivermos um novo
// dijkstra
int orientation(movement *mov) {
    debug_message("Entramos em orientation\n");
    // se voltarmos a onde estavamos anteriormente
    if (mov->anterior == mov->path[mov->path_len]) {
        if (mov->lastRotation) {
            mov->lastRotation = rotation(
                mov->lastRotation,
                mov->boxAttached); // rodamos para dar um 180, basically
            return 1;
        }

        // estamos em 1 ou 8, e damos um belo 180
        mov->lastRotation = rotation(1, mov->boxAttached);
        mov->lastRotation = rotation(1, mov->boxAttached);
        debug_message("180 BABYYYYYY\n");
        return 1;
    }

    if (mov->lastRotation) {
        mov->lastRotation =
            rotation(-mov->lastRotation,
                     mov->boxAttached); // rodamos o inverso de onde estavamos

        return 1;
    }

    mov->lastRotation = rotation(1, mov->boxAttached);
    return 1;
}

// vai buscar a box ao sitio, rotates , goes and backs but with box ;)
// substituir line() por digitalWrite
int box_operations(movement *mov) {
    int line2 = 0, line3 = 0;

    // BEGGINING of test code

    if ((mov->anterior == 2 || mov->anterior == 7) &&
        (mov->atual == 1 || mov->atual == 8)) {
        line2 = 0;
        line3 = 0;
    } else {
        line3 = 1;
        line2 = 1;
    }

    // END of test code

    debug_message("Entramos em Box operations, orientating\n");

    if ((mov->atual != 12)) {
        if (line2 && line3 && (mov->atual != 1) &&
            (mov->atual != 8)) { // substituir line2 e line3 por
            // digitalRead() dos IR correspondentes
            if (mov->turn == RIGHT)
                mov->lastRotation = rotation(1, mov->boxAttached);
            else
                mov->lastRotation = rotation(-1, mov->boxAttached);
            // se estiver no 1 ou 8
        } else if (mov->anterior == 10 || mov->anterior == 15)
            debug_message("No rotation needed\n");
        else
            mov->lastRotation = rotation(1, mov->boxAttached);
    } else if ((mov->origem >= 1) && (mov->origem <= 4))
        mov->lastRotation = rotation(-1, mov->boxAttached);
    else
        mov->lastRotation = rotation(1, mov->boxAttached);

    debug_message("Robot already orientado com box\n");
    if (!motor_go_forward(mov, MISSION)) {
        debug_message("Motor go forward failed on a Mission\nKABUUUUUMMM");
    }

    walk(300, BACKWARDS);

    debug_message("We retrieved box and recuated até intersection detected "
                  "again and a little forward\n");

    return 0;
}

// retorna valor para atualizar mov->lastRotation

// controlo do robot na linha
// verifica interseçao e so sai dps de sair da interseçao
// Vinicius Domain
// type vai definir se é para: buscar/deixar a caixa ou movimento entre nós
// returns 1 if successful, 0 if not
////////////////////////////
// Atualiza o valor de boxAttached
// substituir line1 e line4 por digitalRead ou whatever
int motor_go_forward(movement *mov, int type) {
    int flag = 0; // indica se ja detetamos a interseçao alguma vez or not
    int line1 = 0, line4 = 0; // valores auxiliares para posteriormente
                              // substituir por digitalRead

    // codigo de teste para apagar dps
    if (mov->turn == RIGHT) {
        line4 = 1;
    } else if (mov->turn == LEFT) {
        line1 = 1;
    } else {
        line4 = 1;
        line1 = 1;
    }

    debug_message("Motor a andar para a frente\n");

    if (!type) {
        debug_message("Andamos até ter a caixa\n");
        return 1;
    }

    while (1) {
        walk(1500, FORWARD);

        // esperamos 10ms, para ver se mais algum deste sensor entra na fita
        // or not
        if ((line1 || line4) && !flag) {
            // esperar 10ms mais coisa menos coisa
            delay(10);
            if (line4 && (mov->turn == RIGHT)) {
                debug_message("Detetamos interseçao a direita, correctly\n");
                flag = 1;
                line4 = 0;
            } else if (line1 && (mov->turn == LEFT)) {
                debug_message("Detetamos interseçao a esquerda, correctly\n");
                flag = 1;
                line1 = 0;
            } else if (line4 && (mov->turn == BOTH) && line1) {
                debug_message(
                    "Detetamos interseçao em ambos os lados, correctly\n");

                flag = 1;
                line4 = 0;
                line1 = 0;
            } else {
                debug_message("Intersecao mal detetada\n");
                return 0;
            }
        } else if (flag && (!line1 || line4)) {
            debug_message("We arrived at the end of intersection\n");
            return 1;
        }
    }
}

// vai pegar em dois nós (atual e em path)
void movimentacao(movement *mov) {

    for (int i = 0; i < mov->path_len; i++) {
        char auxs[64];
        sprintf(auxs, "posiçao atual %d, posiçao de destino %d", mov->atual,
                mov->path[mov->path_len]);
        debug_message(auxs);
    }
    // char aux[64];

    // serve para ir de ponto a ponto, very beautiful indeed
    // while (1) {
    //     // esta só a ir até um local
    //     if (!motor_go_forward(mov, AROUND)) {
    //         debug_message("funçao go_forward failed\n");
    //     }
    //     // verificar como funciona k, cause I dont really remember
    //     // vai até local que queremos
    //     mov->anterior = mov->atual;
    //     mov->atual = mov->path[mov->path_len];

    //     // se estiver a caminho do destino
    //     if (mov->atual != mov->destino) {
    //         --mov->path_len;
    //         sprintf(aux, "Intersection number %d\n", mov->path_len + 1);
    //         debug_message(aux);
    //         sprintf(aux, "mov->atual=%d || proximo=%d\n", mov->atual,
    //                 mov->path[mov->path_len]);
    //         debug_message(aux);

    //         // verifica a necessidade de virar or not e atualiza mov->turn
    //         if (detected(mov)) {
    //             mov->lastRotation =
    //                 rotation(_180180360(mov),
    //                          mov->boxAttached); // roda +/- 90 degrees
    //             continue;
    //         }

    //         break;
    //     }
    //     // se estiver no destino, saimos de movimentaçao
    //     break;
    // }
    // return 0;
}

// blue boxes go directly from input to output, and vice-versa
void handle_movement(movement *mov) {
    mov->path_len = dijkstra(mov->path, MAX, mov->origem, mov->destino);
    if (mov->origem) { // não precisavamos de orientar no inicio da prova
        debug_message("roda o robo para o caminho certo\n");
        orientation(mov);
    }
    mov->atual = mov->origem; // robo está na origem
    detected(mov);            // atualiza o valor de mov->turn
    debug_message("Going into movimentaçao\n");
    movimentacao(mov); // anda até mov->destino
    box_operations(
        mov); // vai buscar box e volta atras ate intersection, also rotates
}

movement *new_movement() {
    movement *mov = (movement *)malloc(sizeof(movement));

    mov->boxAttached = 0;
    mov->origem = 0;
    mov->anterior = 0;

    return mov;
}

int factory_lite() {
    factory_lite_setup();
    char colour_code[N_BOXES] = {'X', 'X', 'X', 'X'};
    recieve_colour_code(colour_code, 'I', UDP_ADDRESS);
    for (size_t i = 0; i < N_BOXES; i++) {
        debug_message(colour_code);
    }

    line_case_debug();
    int level = BLUE_LEVEL;
    char input_colour[4] = {'B', 'B', 'B', 'B'};
    char machine_B[4] = {'X', 'X', 'X', 'X'};
    char output_colour[4] = {'X', 'X', 'X', 'X'};

    movement *mov = new_movement();

    switch (LEVEL) {

    case BLUE_LEVEL:
        for (size_t i = 0; i < N_BOXES; i++) {
            mov->destino = i + 1;
            handle_movement(mov);
            input_colour[i] = 'X';
            mov->origem = mov->destino;
            mov->destino = i + 5;
            handle_movement(mov);
            mov->origem = mov->destino;
            output_colour[i] = 'B';
        }
        break;
    }

    return 0;
}