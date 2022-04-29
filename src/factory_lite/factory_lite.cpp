#include "factory_lite.h"

#define MISSION 0 // Buscar/Deixar caixa
#define AROUND 1  // Move around the map

#define ELECTROMAGNET_ON digitalWrite(ELECTROMAGNET, HIGH)
#define ELECTROMAGNET_OFF digitalWrite(ELECTROMAGNET, LOW)
#define ELECTROMAGNET_SETUP pinMode(ELECTROMAGNET, OUTPUT)

int orientation(movement *mov);
int box_operations(movement *mov);
int motor_go_forward(movement *mov, int type);
void movimentacao(movement *mov);
void handle_movement(movement *mov);

void line_setup() {
    pinMode(LINE_SENSOR_1, INPUT);
    pinMode(LINE_SENSOR_2, INPUT);
    pinMode(LINE_SENSOR_3, INPUT);
    pinMode(LINE_SENSOR_4, INPUT);
}

void factory_lite_setup() {
    if (DEBUG_MODE)
        Serial.begin(115200);

    if (USE_WIFI)
        wifi_setup(UDP_ADDRESS, UDP_PORT);
    motors_setup();
    sonar_setup();
    line_setup();
    ELECTROMAGNET_SETUP;
}

// serve para orientar para o sitio certo sempre que tivermos um novo
// dijkstra
int orientation(movement *mov) {
    debug_message("Entramos em orientation\n");
    // se voltarmos a onde estavamos anteriormente
    if (mov->anterior == mov->path[mov->path_len]) {
        if (mov->lastRotation) {
            rotate_line(90, mov->lastRotation, NEMO_SPEED);
            return 1;
        }
        // estamos em 1 ou 8, e damos um belo 180
        rotate_line(90, CLOCKWISE, NEMO_SPEED);
        rotate_line(90, CLOCKWISE, NEMO_SPEED);
        mov->lastRotation = CLOCKWISE;
        debug_message("180 BABYYYYYY\n");
        return 1;
    }

    if (mov->lastRotation) {
        rotate_line(90, -mov->lastRotation,
                    NEMO_SPEED); // rodamos o inverso de onde estavamos
        mov->lastRotation = -mov->lastRotation;

        return 1;
    }

    rotate_line(90, CLOCKWISE, NEMO_SPEED);
    mov->lastRotation = CLOCKWISE;
    return 1;
}

// vai buscar a box ao sitio, rotates , goes and backs but with box ;)
// substituir line() por digitalWrite
int box_operations(movement *mov) {
    debug_message("Entramos em Box operations, orientating\n");

    if ((mov->atual != 12)) {
        if ((LINE_CASE_FAST == LINE) && (mov->atual != 1) &&
            (mov->atual != 8)) { // substituir line2 e line3 por
            // digitalRead() dos IR correspondentes
            if (mov->turn == RIGHT_CURVE) {
                mov->lastRotation = CLOCKWISE;
                rotate_line(90, CLOCKWISE, NEMO_SPEED);
            } else {
                mov->lastRotation = ANTI_CLOCKWISE;
                rotate_line(90, ANTI_CLOCKWISE, NEMO_SPEED);
            }
            // se estiver no 1 ou 8
        } else if (mov->anterior == 10 || mov->anterior == 15) {
            rotate_line(90, CLOCKWISE, NEMO_SPEED);
            mov->lastRotation = CLOCKWISE;
        } else
            debug_message("No rotation needed\n");
    } else if ((mov->origem >= 1) && (mov->origem <= 4)) {
        rotate_line(90, ANTI_CLOCKWISE, NEMO_SPEED);
        mov->lastRotation = ANTI_CLOCKWISE;
    } else {
        rotate_line(90, CLOCKWISE, NEMO_SPEED);
        mov->lastRotation = CLOCKWISE;
    }
    debug_message("Robot already orientado com box\n");

    if (!motor_go_forward(mov, MISSION)) {
        debug_message("Motor go forward failed on a Mission\nKABUUUUUMMM");
    }

    // anda para trás ate detetar interseção
    if (mov->atual == 1 || mov->atual == 8) {
        walk_line(300, BACKWARDS, RIGHT_CURVE);
    } else
        walk_line(300, BACKWARDS, INTERCEPTION);

    // anda para a frente para deixar de detetar interceptio e estar pronto para
    // rodar
    walk_line(100, FORWARD, LEFT_CURVE);

    debug_message("We retrieved box and recuated até intersection detected "
                  "again and a little forward\n");

    return 0;
}

// controlo do robot na linha
// verifica interseçao e so sai dps de sair da interseçao
// type vai definir se é para: buscar/deixar a caixa ou movimento entre nós
// returns 1 if successful, 0 if not
////////////////////////////
// substituir line1 e line4 por digitalRead ou whatever
// precisa de codigo para ir ate ao end da intersection
int motor_go_forward(movement *mov, int type) {
    int flag = 0; // indica se ja detetamos a interseçao alguma vez or not

    debug_message("Motor a andar para a frente\n");

    if (!type) {
        debug_message("Andamos até ter a caixa\n");
        walk_sonar(300, FORWARD);
        ELECTROMAGNET_ON;
        return 1;
    }

    while (1) {
        walk_line(1500, FORWARD, mov->turn);

        if (!flag) {
            if (LINE_CASE_FAST == mov->turn) {
                debug_message("Detetamos interseçao a direita, correctly\n");
            } else if ((LINE_CASE_FAST == mov->turn)) {
                debug_message("Detetamos interseçao a esquerda, correctly\n");
            } else if ((LINE_CASE_FAST == mov->turn)) {
                debug_message(
                    "Detetamos interseçao em ambos os lados, correctly\n");
            } else {
                debug_message("Intersecao mal detetada\n");
            }

            flag = 1;
            mov->turn = LINE;

        } else if (((LINE_CASE_FAST == LINE) || (LINE_CASE_FAST == FREE))) {
            debug_message("We arrived at the end of intersection\n");
            return 1;
        }
    }

    if (mov->atual != mov->destino)
        walk_line(200, FORWARD, INTERCEPTION);
}

// vai pegar em dois nós (atual e em path)
void movimentacao(movement *mov) {
    char aux[64];

    // serve para ir de ponto a ponto, very beautiful indeed
    while (1) {
        // esta só a ir até um local
        if (!motor_go_forward(mov, AROUND)) {
            debug_message("funçao go_forward failed\n");
        }
        // verificar como funciona k, cause I dont really remember
        // vai até local que queremos
        mov->anterior = mov->atual;
        mov->atual = mov->path[mov->path_len];

        // se estiver a caminho do destino
        if (mov->atual != mov->destino) {
            --mov->path_len;
            sprintf(aux, "Intersection number %d\n", mov->path_len + 1);
            debug_message(aux);
            sprintf(aux, "mov->atual=%d || proximo=%d\n", mov->atual,
                    mov->path[mov->path_len]);
            debug_message(aux);

            // verifica a necessidade de virar or not e atualiza mov->turn
            if (detected(mov)) {
                rotate_line(90, _180180360(mov), NEMO_SPEED);
                mov->lastRotation = _180180360(mov);
                continue;
            }

            break;
        }
        // se estiver no destino, saimos de movimentaçao
        break;
    }
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
    // vai buscar box e volta atras ate intersection, also rotates
    box_operations(mov);
}

movement *new_movement() {
    movement *mov = (movement *)malloc(sizeof(movement));

    mov->boxAttached = 0;
    mov->origem = 0;
    mov->anterior = 0;

    return mov;
}

int factory_lite() {
    int aux;
    factory_lite_setup();
    char colour_code[N_BOXES] = {'B', 'B', 'B', 'B'};
    recieve_colour_code(colour_code, 'I', UDP_ADDRESS);

    walk(3000, FORWARD);
    // walk_line(1500, FORWARD, RIGHT_CURVE);
    // rotate_line(90, CLOCKWISE, 140);
    // walk_line(1500, FORWARD, RIGHT_CURVE);
    return 0;
}