#include "temapa.h"
#include "temapa1.h"

Node* creare_Nod(candidati *c)
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL)
    {
        printf("Alocarea dinamica a esuat.");
        exit(1);
    }
    newNode->left = newNode->right = NULL;

    newNode->c = c;
    return newNode;
}

Node* insert_lord(Node *node, float exp, candidati *q)
{
    if(node == NULL) return creare_Nod(q);
    if(exp < node->c->experienta) node->left = insert_lord(node->left, exp,q);
    else if(exp >= node->c->experienta) node->right = insert_lord(node->right,exp,q);
    return node;
}

Node* insert_av_cav(Node *node1, float exp1, candidati *q1)
{
    if(node1 == NULL) return creare_Nod(q1);
    if(exp1 < node1->c->experienta) node1->left = insert_av_cav(node1->left, exp1,q1);
    else if(exp1 >= node1->c->experienta) node1->right = insert_av_cav(node1->right,exp1,q1);
    return node1;
}

void DeQueue(Queue *q, Node **BST_L, Node **BST_A_C)
{
    if(q->front == NULL) return;

    candidati *aux = q->front;
    float aux_experienta = aux->experienta;
    enum statut_social aux_statut = aux->statut;

    q->front = q->front->next;
    if(aux_statut == 1) *BST_L = insert_lord(*BST_L,aux_experienta,aux);
    else if(aux_statut == 2 || aux_statut == 3) *BST_A_C = insert_av_cav(*BST_A_C,aux_experienta,aux);
    if(q->front == NULL) q->rear = NULL;
}

void scriere_BST_Lorzi(Node *root, FILE *f)
{

    if(root == NULL) return;

    scriere_BST_Lorzi(root->right,f);

    fprintf(f,"%s %0.2f %d", root->c->nume, root->c->experienta, root->c->varsta);
    if(root->c->statut == 1)   fprintf(f," LORD\n");
    else if(root->c->statut == 2)  fprintf(f," CAVALER\n");
    else if(root->c->statut == 3)  fprintf(f," AVENTURIER\n");

    scriere_BST_Lorzi(root->left,f);
}

void scriere_BST_C_A(Node *root,FILE *f)
{

    if(root == NULL) return;

    scriere_BST_C_A(root->right,f);
    
    fprintf(f,"%s %0.2f %d", root->c->nume, root->c->experienta, root->c->varsta);
    if(root->c->statut == 1)   fprintf(f," LORD\n");
    else if(root->c->statut == 2)  fprintf(f," CAVALER\n");
    else if(root->c->statut == 3)  fprintf(f," AVENTURIER\n");

    scriere_BST_C_A(root->left,f);
}

void scriere_fisier(Node *BST_L, Node *BST_A_C)
{
    FILE *f_lord = scriereFisier("Pas_2/test_2_lorzi.csv");
    fprintf(f_lord, "Nume Experienta Varsta Statut_social\n");
    scriere_BST_Lorzi(BST_L, f_lord);
    fclose(f_lord);

    FILE *f_a_c = scriereFisier("Pas_2/test_2_cavaleri_aventurieri.csv");
    fprintf(f_a_c, "Nume Experienta Varsta Statut_social\n");
    scriere_BST_C_A(BST_A_C, f_a_c);
    fclose(f_a_c);
}

void elibereaza_BST(Node *root)
{
    if (root == NULL) return;
    elibereaza_BST(root->left);
    elibereaza_BST(root->right);
    free(root->c->nume);
    free(root->c);
    free(root);
}


Node *minNode(Node *node)
{
    if(node == NULL) return NULL;
    while(node->left!=NULL)
    {
        node = node->left;
    }
    return node;
}

Node *deleteNode(Node *root, char *nume, float exp) {
    if (root == NULL) return NULL;

    if (exp < root->c->experienta) {
        root->left = deleteNode(root->left, nume, exp);
    } else if (exp > root->c->experienta) {
        root->right = deleteNode(root->right, nume, exp);
    } else {
        if (root->left == NULL) {
            Node *temp = root->right;
            free(root->c->nume);
            free(root->c);
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node *temp = root->left;
            free(root->c->nume);
            free(root->c);
            free(root);
            return temp;
        }
        Node *temp = minNode(root->right);
        free(root->c->nume);
        *(root->c) = *(temp->c);
        root->c->nume = malloc(strlen(temp->c->nume) + 1);
        if(root->c->nume == NULL)
        {
            printf("Alocarea dinamica a esuat.");
            exit(1);
        }
        if (root->c->nume != NULL) {
            strcpy(root->c->nume, temp->c->nume);
        }
        root->right = deleteNode(root->right, temp->c->nume, temp->c->experienta);
    }

    return root;
}

void prelucrareContestatii(Node **BST_L) {
    FILE *f = deschideFisier("Pas_3/contestatii.csv");

    char info_contest[200];
    fgets(info_contest, sizeof(info_contest), f);

    while (fgets(info_contest, sizeof(info_contest), f)) {
        info_contest[strcspn(info_contest, "\n")] = '\0';

        char *nume_aux = strtok(info_contest, ";");
        char *exp_aux = strtok(NULL, ";");
        char *varsta_aux = strtok(NULL, ";");

        char *nume = nume_fin(nume_aux);
        float exp = atof(exp_aux);

        *BST_L = deleteNode(*BST_L, nume, exp);
        free(nume);
    }

    fclose(f);
}

