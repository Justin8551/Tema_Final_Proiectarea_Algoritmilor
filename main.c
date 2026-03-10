#include "temapa.h"
#include "temapa1.h"
#include "temapa2.h"
#include "temapa3.h"

int main() {
	Queue *q;
	q=create_Queue();
	EnQueue(q);
	scriere(q);
	//pasul_1
	
	Node *BST_Lorzi=NULL;
	Node *BST_Aventurieri_Cavaleri=NULL;

	while(!isEmpty(q)) DeQueue(q, &BST_Lorzi, &BST_Aventurieri_Cavaleri);
		scriere_fisier(BST_Lorzi,BST_Aventurieri_Cavaleri);
	//pasul_2
	
	prelucrareContestatii(&BST_Lorzi);
	FILE *f_Lord_final = scriereFisier("Pas_3/test_3_lorzi.csv");
	fprintf(f_Lord_final, "Nume Experienta Varsta Statut_social\n");
	scriere_BST_Lorzi(BST_Lorzi, f_Lord_final);
	fclose(f_Lord_final);
	//pasul_3
	
	Heap *h = create_Heap(8);
	Node *BST_topL[4] = {NULL};
	Node *BST_topAC[4] = {NULL};
	int i=0, j=0;

	extragere_max(BST_Lorzi,BST_topL,&i);
	extragere_max(BST_Aventurieri_Cavaleri,BST_topAC,&j);

	Traseu trasee[8];
	extragere_traseu(trasee,"Pas_4/trasee.csv");
	
	for (int k = 0; k < 4; k++)
	{
    Participant p_Lord = creare_Lord(BST_topL, trasee, k);
    insert_Heap(&h, p_Lord);

    Participant p_AC = creare_Aventurier_Cavaler(BST_topAC, trasee, k);
    insert_Heap(&h, p_AC);
	}
	scrie_Heap(&h, "Pas_4/test_4.csv");
	//pasul_4

	Heap *heap_exp;
	heap_exp = actualizare_exp(h,trasee);
	scrie_Heap(&heap_exp, "Pas_5/test_5.csv");
	//pasul_5

	premiere(heap_exp);
	//pasul_6

	
	Graf *g;
	g=creare_Graf();
	int vizitat[11];
	for(int i=0;i<11;i++)
	{
		vizitat[i]=0;
	}
	grade_ies_int(g);
	int drum[6];
	for(int i=0;i<5;i++)
	{
		drum[i]=0;
	}
	int nr_curent=0;
	FILE *f = scriereFisier("Pas_7/test_7.csv");
	for(int i=0;i<g->nr_varfuri;i++)
	{
		if(g->grade_intrare[i]==0)
		{
			dfs(g, vizitat, drum, 0, i, &nr_curent,f);
		}
	}
	fclose(f);
	//pasul_7

	elibereaza_BST(BST_Lorzi);
	elibereaza_BST(BST_Aventurieri_Cavaleri);
	elibereazaCoada(q);
	eliberare_Heap(&h);
	eliberare_Heap(&heap_exp);
	elibereazaGraf(g);
	return 0;
}