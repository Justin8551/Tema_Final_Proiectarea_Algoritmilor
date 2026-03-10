#include "temapa.h"

Queue* create_Queue()
{
    Queue *q;
    q=(Queue*)malloc(sizeof(Queue));
    if(q==NULL)
    {
        printf("Alocarea dinamica a esuat.");
        exit(1);
    }

    q->front=q->rear=NULL;
    return q;
}

FILE* deschideFisier(char* nume_fisier) {
    FILE *f = fopen(nume_fisier, "r");
    if (f == NULL) {
        printf("Fisierul nu a fost deschis.");
        exit(1);
    }
    return f;
}

FILE* scriereFisier(char* nume_fisier)
{
    FILE *f = fopen(nume_fisier, "w");
    if(f == NULL)
    {
        printf("Fisierul nu a fost deschis.");
        exit(1);
    }
    return f;
}

candidati* alocaCandidat() {
    candidati *newCand = (candidati*)malloc(sizeof(candidati));
    if (newCand == NULL) {
        printf("Alocarea dinamica a esuat.\n");
        exit(1);
    }
    return newCand;
}

int isEmpty(Queue *q){
   return (q->front == NULL);
}

char* nume_fin(char *prim_nume)
{
    char *nume_final = (char*)malloc(strlen(prim_nume) + 1);
    if (nume_final == NULL)
    {
        printf("Alocarea dinamica a esuat.");
        exit(1);
    }
    if(prim_nume != NULL) strcpy(nume_final, prim_nume);
    
    while (1)
    {
        char *urm_nume = strtok(NULL, " ");
        if (urm_nume == NULL) break;

        char *temp = realloc(nume_final, strlen(nume_final) + strlen(urm_nume)+2);
        if (temp == NULL)
        {
            free(nume_final);
            printf("Alocarea dinamica a esuat.");
            exit(1);
        }

        nume_final = temp;
        strcat(nume_final, "-");
        strcat(nume_final, urm_nume);
    }

    int i = 0;
    while (nume_final[i] != '\0')
    {
        if (i == 0 || nume_final[i - 1] == '-') {
            nume_final[i] = toupper(nume_final[i]);
         } else 
         {
           nume_final[i] = tolower(nume_final[i]);
         }
        i++;
    }

    return nume_final;
}

void EnQueue(Queue *q)
{
    FILE *f = deschideFisier("Pas_1/candidati.csv"); 

    char info_cand[200];
    fgets(info_cand,sizeof(info_cand),f);
    
    while(fgets(info_cand, sizeof(info_cand), f))
    {
        candidati *newCand = alocaCandidat();
        info_cand[strcspn(info_cand,"\n")]='\0';

        char *statutsinume = strtok(info_cand, ";");
        char *experienta = strtok(NULL, ";");
        char *varsta = strtok(NULL, ";");

        char statut[20], nume_prov[100];
        strcpy(statut,strtok(statutsinume," "));
        strcpy(nume_prov,strtok(NULL," "));
        
        for (int i = 0; i < strlen(statut); i++)
            statut[i] = toupper(statut[i]);

        if(strcmp(statut,"LORD") == 0) newCand->statut = 1;
        else if(strcmp(statut,"CAVALER") == 0) newCand->statut = 2;
        else if(strcmp(statut,"AVENTURIER") == 0) newCand->statut = 3;

        char *nume_complet = nume_fin(nume_prov);
        newCand->nume = nume_complet;


        float exp = atof(experienta);
        newCand->experienta = exp;

        int vst = atoi(varsta);
        newCand->varsta = vst;

        newCand->next = NULL;
        if(q->rear == NULL)
        {
            q->front = q->rear = newCand;
        }
        else
        {
            q->rear->next = newCand;
            q->rear = newCand;
        }   
    }
    fclose(f);
}

void scriere(Queue *q)
{
    FILE *f = scriereFisier("Pas_1/test_1.csv");
    fprintf(f, "Nume Experienta Varsta Statut_social\n");

    candidati *temp = q->front;
    while (temp != NULL)
    {
        fprintf(f, "%s %.2f %d", temp->nume, temp->experienta, temp->varsta);
        if(temp->statut == 1)   fprintf(f," LORD\n");
        else if(temp->statut == 2)  fprintf(f," CAVALER\n");
        else if(temp->statut == 3)  fprintf(f," AVENTURIER\n");
        temp = temp->next;
    }
    fclose(f);
}

void elibereazaCoada(Queue *q)
{
    candidati *temp = q->front;
    while (temp != NULL)
    {
        candidati *temp1 = temp;
        temp = temp->next;
        
        free(temp1->nume);
        free(temp1);
    }
    q->front = NULL;
    q->rear = NULL;
    free(q);
}