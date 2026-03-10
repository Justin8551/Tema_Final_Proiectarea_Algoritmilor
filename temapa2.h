#ifndef TEMAPA2_H
#define TEMAPA2_H
#include "temapa.h"
#include "temapa1.h"

typedef struct
{
    char nume[3];
    int paduri[10];
    int nrpaduri;
}Traseu;

typedef struct
{
    char nume[100];
    float experienta;
    Traseu traseu;
}Participant;

typedef struct
{
    Participant *max_heap;
    int size;
    int capacity;
}Heap;

Heap* create_Heap(int capacitate);
void extragere_traseu(Traseu *vec, char *nume_fisier);
void resize(Heap *h);
void extragere_max(Node *BST, Node **BST_prim, int *i);
void insert_Heap(Heap **h, Participant p);
Participant creare_Lord(Node **top, Traseu *trasee, int i);
Participant creare_Aventurier_Cavaler(Node **top, Traseu *trasee, int i);
void scrie_Heap(Heap **h, char* numeFisier);

Heap* actualizare_exp(Heap *h, Traseu *trasee);
void swap(Participant* a, Participant* b);
void premiere(Heap *h);

void eliberare_Heap(Heap **h);
#endif