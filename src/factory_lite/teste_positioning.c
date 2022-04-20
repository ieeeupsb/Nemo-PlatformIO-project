#include "positioning.h"

int main(int argc, char const *argv[])
{
    movement *mov=malloc(sizeof(movement));

    mov->origem=2;
    mov->destino=5;
    mov->k=dijkstra(mov->path,MAX, mov->origem, mov->destino);
    printf("\nO path tem %d elementos\n", mov->k);
    mov->atual=mov->origem;
    printf("We are at %d e vamos para %d\n", mov->atual, mov->path[mov->k]);
    detected(mov);  
    printf("Vamos detetar a %d na next intersection\n", mov->turn);


    return 0;
}
