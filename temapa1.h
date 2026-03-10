#ifndef TEMAPA1_H
#define TEMAPA1_H
#include "temapa.h"

typedef struct Node
{
    candidati *c;
    struct Node *left, *right;
}Node;

Node* creare_Nod(candidati *c);
Node* insert_lord(Node *node, float exp, candidati *q);
Node* insert_av_cav(Node *node1, float exp1, candidati *q1);
void DeQueue(Queue *q, Node **BST_L, Node **BST_A_C);
void scriere_BST_Lorzi(Node *root, FILE *f);
void scriere_BST_C_A(Node *root, FILE *f);
void scriere_fisier(Node *BST_L, Node *BST_A_C);
void elibereaza_BST(Node *root);

Node *minNode(Node *node);
Node *deleteNode(Node *root, char *nume, float exp);
void prelucrareContestatii(Node **BST_L);

#endif