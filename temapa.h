#ifndef TEMAPA_H
#define TEMAPA_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

enum statut_social
{
    LORD=1, CAVALER=2, AVENTURIER=3
};

typedef struct date 
{
    char *nume;
    int varsta;
    float experienta;
    enum statut_social statut;
    struct date* next;
}candidati;


typedef struct
{
    candidati *front, *rear;
}Queue;

Queue* create_Queue();
FILE* deschideFisier(char* nume_fisier);
FILE* scriereFisier(char* nume_fisier);
candidati* alocaCandidat();
int isEmpty(Queue *q);
char* nume_fin(char *nume_prov);
void EnQueue(Queue *q);
void scriere(Queue *q);
void elibereazaCoada(Queue *q);

#endif