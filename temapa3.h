#ifndef TEMAPA3_H
#define TEMAPA3_H
#include "temapa.h"
#include "temapa1.h"
#include "temapa2.h"

typedef struct
{
    int nr_varfuri;
    int **matrice_adiacenta;
    int grade_iesire[11];
    int grade_intrare[11];
}Graf;

Graf * alocGraph (int val);
Graf* creare_Graf();
void grade_ies_int(Graf *g);
void dfs(Graf *g, int *vizitat, int *drum, int nr, int i, int *nr_curent, FILE *f);
void elibereazaGraf(Graf* graf);
#endif