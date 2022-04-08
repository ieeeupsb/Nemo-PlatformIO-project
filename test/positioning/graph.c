#include <positioning.h>
#include <stdlib.h>
#include <sensors.h>

/*UDP commands
receive_color_code(char* color_code, char local(I, O, A, B));   
*/


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

typedef enum colour{RED, BLUE, GREEN};
int box=0;      //inteiro que indica se entrou no ramo de uma intercacao or not

//controlo do robot na linha
//verifica interseçao e so sai dps de sair da interseçao
//Vinicius Domain
//vai utilizar 
//returns 1 if successful, 0 if not
int motor_go_forward(movement *mov){


}

//vai pegar em dois nós (atual e em path)
int movimentacao(movement *mov){
    
    switch(box){

        //esta só a ir até um local
        case 0:
            if(!motor_go_forward(mov){
                printf("funçao go_forward failed\n");
            }
        --k;
        //verificar como funciona k, cause I dont really remember
        if(k!=0){
            mov->atual=mov->path[k];
            update_intersection(mov);
            printf("Na proxima Interseção vamos virar a %d", mov->turn;
        }

    }

}


void handle_blue(movement *mov){
    mov->k=djikstra(mov->path[], MAX, mov->origem, mov->destino);
    mov->atual=mov->origem;
    movimentacao(mov);
    mov->k=dijkstra(mov->path[], MAX, mov->origem, mov->destino);
    movimentacao();

}


typedef struct _rota
{
    movement *mov;
    unsigned int n_viagens;
    unsigned int *distancia_rota;
    int atual;      //must recent position
} rota;

int disk() {
    return 3;
}

void adicionar_viagem(rota r, movement mov) {
    r.lista_de_viagens[r.n_viagens] = v;
    r.n_viagens += 1;
    r.distancia_de_rota += v.distancia;
}

movement criar_viagem(int inicio, int fim[2]) {
    movement mov ;
    v.inicio = inicio;
    v.fim = fim;
    v.distancia = disk();
    
    return v; 
}



int main() {

    int i=0, j=0;

    char color_code[4] = {'G', 'G', 'G', 'G'};
    char machine_A[4] = {'G', 'X', 'X', 'G'};
    char machine_B[4] = {'X', 'X', 'X', 'X'};

    rota *r=malloc(sizeof(rota));
        r->mov=calloc(20, sizeof(movement));
        r->distancia_rota=calloc(20, sizeof(int));

    for(i=0;i<4;i++){
        switch(color_code[i]){

            case 'B':   handle_blue();

            case 'G':   handle_green();

            case 'R':   handle_red();
        }

    }



{
    /*
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
    */
}
}