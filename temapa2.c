#include "temapa.h"
#include "temapa1.h"
#include "temapa2.h"

Heap* create_Heap(int capacitate)
{
    Heap *h = (Heap*)malloc(sizeof(Heap));
    if(h == NULL)
    {
        printf("Alocarea dinamica a esuat.");
        exit(1);
    }
    h->size=0;
    h->capacity=capacitate;
    h->max_heap=(Participant*)malloc(sizeof(Participant)*h->capacity);
    if(h->max_heap == NULL)
    {
        printf("Alocarea dinamica a esuat.");
        exit(1);
    }
    return h;
}

void extragere_traseu(Traseu *vec, char *nume_fisier)
{
    FILE *f = deschideFisier(nume_fisier);
    char linie[256];
    int nr=0;
    while(fgets(linie,sizeof(linie), f))
    {
        char *nume_aux = strtok(linie,":");
        linie[strcspn(linie,"\n")]='\0';
        if(nume_aux)
        {
            strcpy(vec[nr].nume,nume_aux);
            vec[nr].nrpaduri=0;
        }

        char *paduri_aux = strtok(NULL," ");
        while(paduri_aux)
        {
            vec[nr].paduri[vec[nr].nrpaduri] = atoi(paduri_aux);
            vec[nr].nrpaduri++;
            paduri_aux = strtok(NULL," ");
        }
        nr++;
    }
    fclose(f);
}

void resize(Heap *h)
{
    h->capacity = 2*h->capacity;
    Participant *v = (Participant*)realloc(h->max_heap,sizeof(Participant)*h->capacity);
    if(v == NULL)
    {
        printf("Realocarea a esuat.");
        h->capacity = h->capacity/2;
        exit(1);
    }
    h->max_heap = v;
}

void extragere_max(Node *BST, Node **BST_prim, int *i)
{
    if (BST == NULL || *i > 3) {
        return;
    }

    extragere_max(BST->right,BST_prim, i);
    if((*i) <= 3)
    {
        BST_prim[(*i)] = BST;
        (*i)++;
    }
    extragere_max(BST->left,BST_prim,i);
}

void insert_Heap(Heap **h, Participant p)
{
    int i;
    if((*h)->size == (*h)->capacity) resize(*h);
    i = (*h)->size;
    (*h)->size++;
    while(i > 0 && p.experienta > (*h)->max_heap[(i-1)/2].experienta)
    {
        (*h)->max_heap[i] = (*h)->max_heap[(i-1)/2];
        i = (i-1)/2;
    }
    (*h)->max_heap[i] = p;
}

Participant creare_Lord(Node **top, Traseu *trasee, int i)
{
    Participant p;
    strcpy(p.nume, top[i]->c->nume);
    p.experienta = top[i]->c->experienta;
    p.traseu = trasee[2 * i];
    return p;
}

Participant creare_Aventurier_Cavaler(Node **top, Traseu *trasee, int i)
{
    Participant p;
    strcpy(p.nume, top[i]->c->nume);
    p.experienta = top[i]->c->experienta;
    p.traseu = trasee[2 * i + 1];
    return p;
}

void scrie_Heap(Heap **h, char* numeFisier) {
    FILE *f = scriereFisier(numeFisier);
    fprintf(f , "Nume_Traseu - Nume_Participant (Experienta_participant)\n");
    for (int i = 0; i < (*h)->size; i++) {
        fprintf(f, "%s - %s (%.2f)\n", (*h)->max_heap[i].traseu.nume,(*h)->max_heap[i].nume,(*h)->max_heap[i].experienta);
    }
    fclose(f);
}


Heap* actualizare_exp(Heap *h, Traseu *trasee)
{
    Heap *sortat=create_Heap(8);
    for(int i = 0; i < h->size; i++)
    {
        int aux=0;
        for(int j=0; j<h->max_heap[i].traseu.nrpaduri; j++)
        {
            aux+=h->max_heap[i].traseu.paduri[j];
        }
        h->max_heap[i].experienta+=aux;
        insert_Heap(&sortat,h->max_heap[i]);
    }
    return sortat;
}

void swap(Participant* a, Participant* b)
{
    Participant aux = *a;
    *a = *b;
    *b = aux;
}

void premiere(Heap *h)
{   
    Heap *aux = create_Heap(3);
    FILE *f = scriereFisier("Pas_6/test_6.csv");
    fprintf(f, "Nume Experienta_totala\n");
    for(int i=0;i<3;i++)
    {
        insert_Heap(&aux,h->max_heap[i]);
    }

    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(aux->max_heap[i].experienta < aux->max_heap[j].experienta)
            {
                swap(&aux->max_heap[i], &aux->max_heap[j]);
            }
        }
    }
    
    for(int i=2;i>=0;i--)
    {
        fprintf(f,"%s %0.2f\n", aux->max_heap[i].nume, aux->max_heap[i].experienta);
    }
    eliberare_Heap(&aux);
    fclose(f);
}


void eliberare_Heap(Heap **h)
{
    if (*h==NULL) return;
    free((*h)->max_heap);
    free(*h);
}


