#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 19
#define INFINITY 4000

enum turning { RIGHT, LEFT, BOTH };

// Matriz G das distancias entre pontos
//é essencial, saber de que lado deteto cada vertice, porque assim sei para onde
// estou a ir e a minha actual location De forma a saber se tem de ser direita
// ou
// esquerda, vamos considerar as colunas os sitios para onde têm de ir, e as
// linhas o sitio de onde começam para isso vamos usar numeros positivos para
// conhecer a direita, e numeros negativos para a esquerda

// o facto de criar uma estrutura aqui, n significa que seja uma variavel global
// :), debugging for 30 min to find out that shit
typedef struct _movement {
    int origem;        // onde comecei e para onde vou
    int destino;       // onde quero chegar
    size_t path_len;   // numero de elementos em path, vai decrementando
    int path[MAX];     // caminho a tomar
    int atual;         // must recent position
    int anterior;      // last position
    enum turning turn; // saber qual o proximo lado a detetar
    int boxAttached;   // indica se tem box attached or not
    int lastRotation;  // last direction this mf rotated
} movement;

// To be honest dei CTRL+C de um code que vi online para dijkstra
// Works well though, mas provavelmente estamos a fazer passos a mais porque eu
// n sabia limitar os mesmos returns k gives shortest path through vector
// path[MAX], for robot to go
int dijkstra(int j[], int n, int startnode, int finishnode);

// detetou a interseçao que estavamos a espera
// para navegaçao ao longo do caminho
int detected(movement *mov);

int _180180360(movement *mov);
