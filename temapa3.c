#include "temapa.h"
#include "temapa1.h"
#include "temapa2.h"
#include "temapa3.h"

Graf* alocGraph (int val)
{
    int i, j ;
    Graf *g =(Graf*) malloc(sizeof(Graf));
    if (g==NULL) return NULL;
    (g->nr_varfuri)=val;
    g->matrice_adiacenta = (int**)malloc(sizeof(int*)*g->nr_varfuri);
    for (i=0;i<g->nr_varfuri;i++)
    {
        g->matrice_adiacenta[i]=(int*)calloc(g->nr_varfuri,sizeof(int));
    }
    return g;
}
 
Graf* creare_Graf()
{
    FILE *f = deschideFisier("Pas_7/drumuri.csv");
    Graf *g = alocGraph(11);
    char info_drum[6];
    while(fgets(info_drum,sizeof(info_drum),f))
    {
        info_drum[strcspn(info_drum,"\n")]='\0';
        int varf_de_iesire=0;
        int varf_de_intrare=0;
        char *vie=strtok(info_drum," ");
        char *vin=strtok(NULL," ");
        if(vie && vin)
        {
            varf_de_iesire = atoi(vie);
            varf_de_intrare = atoi(vin);
            g->matrice_adiacenta[varf_de_iesire][varf_de_intrare]=1;
        }
    }
    fclose(f);
    return g;
}

void grade_ies_int(Graf *g)
{
    int grad_iesire;
    for(int i=0;i<g->nr_varfuri;i++)
    {
        grad_iesire=0;
        for(int j=0;j<g->nr_varfuri;j++)
        {
            grad_iesire+=g->matrice_adiacenta[i][j];
        }
        g->grade_iesire[i] = grad_iesire;
    }

    int grad_intrare;
    for(int j=0;j<g->nr_varfuri;j++)
    {
        grad_intrare=0;
        for(int i=0;i<g->nr_varfuri;i++)
        {
            grad_intrare+=g->matrice_adiacenta[i][j];
        }
        g->grade_intrare[j] = grad_intrare;
    } 
}

void dfs(Graf *g, int *vizitat, int *drum, int nr, int i, int *nr_curent, FILE *f)
{
    vizitat[i] = 1;
    drum[nr] = i;
    nr++;

    if (g->grade_iesire[i] == 0)
    {
        fprintf(f,"T%d: ", (*nr_curent)+1);
        (*nr_curent)++;

        for (int i = 0; i < nr; i++) {
            fprintf(f,"%d ", drum[i]);
        }
        fprintf(f,"\n");
    }

    for (int v = 0; v < g->nr_varfuri; v++) 
    {
        if (g->matrice_adiacenta[i][v] && !vizitat[v]) 
        {
            dfs(g, vizitat, drum, nr, v,nr_curent,f);
        }
    }

    vizitat[i] = 0;
}

void elibereazaGraf(Graf* graf) {
    if (graf == NULL) return;

    for (int i = 0; i < graf->nr_varfuri; i++) {
        free(graf->matrice_adiacenta[i]);
    }
    free(graf->matrice_adiacenta);
    free(graf);
}
