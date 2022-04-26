#include "positioning.h"

int G[MAX][MAX] = {
    {INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY,
     INFINITY, INFINITY, 212, INFINITY, -1, INFINITY, INFINITY, INFINITY,
     INFINITY, 692, INFINITY, INFINITY},
    {INFINITY, INFINITY, -150, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY,
     INFINITY, INFINITY, -362, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY,
     INFINITY, INFINITY, INFINITY},
    {INFINITY, 150, INFINITY, -150, INFINITY, INFINITY, INFINITY, INFINITY,
     INFINITY, INFINITY, -1, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY,
     INFINITY, INFINITY, INFINITY},
    {INFINITY, INFINITY, 150, INFINITY, -150, INFINITY, INFINITY, INFINITY,
     INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY,
     INFINITY, INFINITY, INFINITY, INFINITY},
    {INFINITY, INFINITY, INFINITY, 150, INFINITY, INFINITY, INFINITY, INFINITY,
     INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, 1, INFINITY, INFINITY,
     INFINITY, 242, INFINITY},
    {INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, 150, INFINITY,
     INFINITY, INFINITY, INFINITY, 1, INFINITY, INFINITY, INFINITY, INFINITY,
     242, INFINITY, INFINITY},
    {INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, -150, INFINITY, 150,
     INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY,
     INFINITY, INFINITY, INFINITY, INFINITY},
    {INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, -150, INFINITY,
     150, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, -1,
     INFINITY, INFINITY, INFINITY},
    {INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, -150,
     INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, -362,
     INFINITY, INFINITY, INFINITY},
    {-212, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY,
     INFINITY, INFINITY, 150, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY,
     -1, INFINITY, INFINITY},
    {INFINITY, 362, 1, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY,
     INFINITY, -150, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY,
     INFINITY, INFINITY, INFINITY},
    {1, INFINITY, INFINITY, INFINITY, INFINITY, -1, INFINITY, INFINITY,
     INFINITY, INFINITY, INFINITY, INFINITY, 150, INFINITY, INFINITY, INFINITY,
     212, INFINITY, INFINITY},
    {INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY,
     INFINITY, INFINITY, INFINITY, INFINITY, 150, INFINITY, 150, INFINITY,
     INFINITY, INFINITY, INFINITY, INFINITY},
    {INFINITY, INFINITY, INFINITY, INFINITY, -1, INFINITY, INFINITY, INFINITY,
     INFINITY, INFINITY, INFINITY, INFINITY, 150, INFINITY, INFINITY, INFINITY,
     INFINITY, 212, 1},
    {INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY,
     INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY,
     INFINITY, 150, INFINITY, -1, -212},
    {INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, 1,
     362, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, -150, INFINITY,
     INFINITY, INFINITY, INFINITY},
    {692, INFINITY, INFINITY, INFINITY, INFINITY, 242, INFINITY, INFINITY,
     INFINITY, 1, INFINITY, -212, INFINITY, INFINITY, INFINITY, INFINITY,
     INFINITY, INFINITY, INFINITY},
    {INFINITY, INFINITY, INFINITY, INFINITY, 242, INFINITY, INFINITY, INFINITY,
     INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, -212, 1, INFINITY,
     INFINITY, INFINITY, 692},
    {INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY,
     INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, -1, 212,
     INFINITY, INFINITY, -692, INFINITY}};

// To be honest dei CTRL+C de um code que vi online para dijkstra
// Works well though, mas provavelmente estamos a fazer passos a mais porque eu
// n sabia limitar os mesmos returns k gives shortest path through vector
// path[MAX], for robot to go
int dijkstra(int j[], int n, int startnode, int finishnode) {

    int distance[MAX], pred[MAX];
    int visited[MAX], count, mindistance, nextnode = 0, i, k;

    // pred[] stores the predecessor of each node
    // count gives the number of nodes seen so far
    // initialize pred[],distance[] and visited[]
    for (i = 0; i < n; i++) {
        if (abs(G[startnode][i]) < 6) {
            distance[i] = INFINITY;
        } else
            distance[i] = abs(G[startnode][i]);

        pred[i] = startnode;
        visited[i] = 0;
    }

    distance[startnode] = 0;
    visited[startnode] = 1;
    count = 1;
    while (count < n - 1) {
        mindistance = INFINITY;
        // nextnode gives the node at minimum distance
        for (i = 0; i < n; i++)
            if (distance[i] < mindistance && !visited[i]) {
                mindistance = distance[i];
                nextnode = i;
            }
        // check if a better path exists through nextnode
        visited[nextnode] = 1;
        for (i = 0; i < n; i++)
            if (!visited[i]) {
                if (abs(G[nextnode][i]) > 6)
                    if (mindistance + abs(G[nextnode][i]) < distance[i]) {
                        distance[i] = mindistance + abs(G[nextnode][i]);
                        pred[i] = nextnode;
                    }
            }
        count++;
    }

    // print the path and distance of each node

    printf("\nDistance of node %d=%d", finishnode, distance[finishnode]);
    j[0] = finishnode;
    k = 1;
    printf("\nPath: %d", j[0]);

    do {
        j[k] = pred[j[k - 1]];

        k++;
        printf("<-%d", j[k - 1]);
    } while (j[k - 1] != startnode);

    printf("\n");
    return k - 2;
}

// detetou a interseçao que estavamos a espera
// para navegaçao ao longo do caminho
int detected(movement *mov) {
    // se k=0, ent ja chegamos ao nosso destino, por isos devemos passar a
    // proxima açao
    if (mov->k < 0) {
        printf("\nTime to go into the BOOXXXX\n");
        return -1;
    }

    // para ir atualizando os vertices conforme vamoooos
    if ((mov->atual == 13) || (mov->atual == 11) ||
        ((mov->atual == 2) && (mov->path[mov->k] == 1)) ||
        ((mov->atual == 7) && (mov->path[mov->k] == 8))) {
        mov->turn = BOTH;
        printf("Proxima intersection detetamos no meio\n");
    } else if (G[mov->atual][mov->path[mov->k]] > 0) {
        mov->turn = RIGHT;
        printf("Proxima intersection detetamos a direita\n");
    } else {
        mov->turn = LEFT;
        printf("Proxima intersection detetamos a esquerda\n");
    }

    return 1;
}

int _180180360(movement *mov) {

    return G[mov->path[mov->k + 2]][mov->path[mov->k]];
}

/*
//codigo de teste
int main(){
        movement *mov=malloc(sizeof(movement));

        mov->origem=3;
        mov->destino=7;
        mov->k=dijkstra(mov->path,MAX, mov->origem, mov->destino);
        printf("\nO path tem %d elementos\n", mov->k);
        mov->atual=mov->origem;
        printf("We are at %d e vamos para %d\n", mov->atual, mov->path[mov->k]);
        detected(mov);
        printf("Vamos detetar a %d na next intersection\n", mov->turn);

}

*/