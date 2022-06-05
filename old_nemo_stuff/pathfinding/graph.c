#define ST 0

#define I0 1
#define I1 2
#define I2 3
#define I3 4

#define O0 5
#define O1 6
#define O2 7
#define O3 8

#define A0 9
#define A1 10
#define A2 11
#define A3 12

#define B0 13
#define B1 14
#define B2 15
#define B3 16


#include<stdlib.h>

typedef struct viagem
{
    int inicio;
    int fim;
    unsigned int distancia;
} viagem;

typedef struct rota
{
    viagem lista_de_viagens[4];
    unsigned int n_viagens;
    unsigned int distancia_de_rota;
} rota;

int disk() {
    return 3;
}

void adicionar_viagem(rota r, viagem v) {
    r.lista_de_viagens[r.n_viagens] = v;
    r.n_viagens += 1;
    r.distancia_de_rota += v.distancia;
}

viagem criar_viagem(int inicio, int fim[2]) {
    viagem v;
    v.inicio = inicio;
    v.fim = fim;
    v.distancia = disk();
    
    return v; 
}


char* solution[81];

int main() {

    char color_code[4] = {'G', 'G', 'G', 'G'};
    char machine_A[4] = {'X', 'X', 'X', 'X'};
    char machine_B[4] = {'X', 'X', 'X', 'X'};

    viagem lista_de_viagens[9];

    int pos = 0;

    lista_de_viagens[pos++] = criar_viagem(ST, I0);
    switch (color_code[0])
    {
    case 'B':
        lista_de_viagens[pos] = criar_viagem(I0, O0);
        pos += 2;
        break;
    
    case 'G':
        lista_de_viagens[pos++] = criar_viagem(I0, B0);
        lista_de_viagens[pos++] = criar_viagem(B0, B2);
        lista_de_viagens[pos] = criar_viagem(B2, O0);
        pos += 2;
        break;
    
    case 'R':
        lista_de_viagens[pos++] = criar_viagem(I0, A0);
        lista_de_viagens[pos++] = criar_viagem(A0, A2);
        lista_de_viagens[pos++] = criar_viagem(A2, B0);
        lista_de_viagens[pos++] = criar_viagem(B0, B2);
        lista_de_viagens[pos++] = criar_viagem(B2, O0);
        break;
    }

    lista_de_viagens[pos++] = criar_viagem(O0, I1);

    int n_viagens = pos;
    pos = 0;
}