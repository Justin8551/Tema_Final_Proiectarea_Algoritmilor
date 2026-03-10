DUMITRU GABRIEL JUSTIN 312AB
Tema Proiectarea Algoritmilor


1. temapa.c/temapa.h

A) Structura date
i. numele candidatului (char*)
ii. vârsta candidatului (int)
iii. experiența candidatului (float)
iiii. statutul candidatului (struct enum)
iiiii. urmatorul candidat in coada (date*)

B) Structura Queue
i. inceputul și finalul cozii (candidati*)

C) Queue* create_Queue()
Funcție generala pentru crearea unei cozi. Se aloca dinamic memorie pentru coada, apoi inceputul si sfarsitul cozii sunt inițializate cu "NULL" și se returneaza coada. O(1)

D) FILE* deschideFisier(char* nume_fisier)
Funcție folosită pentru a permite acces de reading pentru un fisier stabilit testând totodata și funcționalitatea, returnând fișierul. O(1)

E) FILE* scriereFisier(char* nume_fisier)
Funcție folosită pentru a permite acces de writing pentru un fisier stabilit testând totodata și funcționalitatea, returnând fișierul. o(1)

F) candidati* alocaCandidat()
Funcție folosită pentru alocarea dinamica a unei variabile de tip candidati, returnand variabila "newCand". O(1)

G) int isEmpty(Queue *q)
Funcție generală pentru a verifica dacă coada este goala, returnând 0 sau 1. O(1)

H)char* nume_fin(char *nume_prov)
Funcție folosită pentru a concatena caracterul "-" intre numele candidatului. Alocă dinamic spațiu pentru numele final și copiază numele inițial. Desparte numele în cuvinte folosind spațiul ca delimitator, iar dacă există alte cuvinte, realocă dinamic suficient spațiu pentru a adăuga cratima și cuvântul următor. La final, parcurge fiecare caracter din șirul rezultat, transformând prima literă din fiecare cuvânt în literă mare și pe celelalte în litere mici. Funcția returnează numele corect. O(n^2) - timp, O(n) - spatiu

I)void EnQueue(Queue *q)
Funcție de adaugare in coada a candidaților citiți și prelucrați din fișierul "candidati.csv". Citim liniile din fișier intr-un buffer, unde se afla toate informațiile candidatului, alocam dinamic spațiu pentru candidat si eliminăm "\n" din finalul șirului "info_cand". Salvăm toate informațiile necesare in variabile auxiliare si le prelucram cu ajutorul funcțiilor predefinite, ulterior atasând la finalul cozii variabila "newCand" cu informațiile stabilite și inchid fișierul. O(n^2) - timp, O(s) - spatiu 

J)void scriere(Queue *q)
Funcție de scriere a cozii in fisierul "test_1.csv". Aceasta scrie prima propozitie deja definita, urmand sa scrie in fișier datele de ieșire prelucrate și sa inchidă fișierul. O(n) - timp, O(1) - spatiu

K)void elibereazaCoada(Queue *q)
Funcție generală de eliberare a memoriei alocate dinamic specifică cozii. O(m)


2) temapa1.c/temapa1.h

A)Structura Node
i. informațiile candidatului (candidati*)
ii. pointer catre nodulul din stanga/dreapta (Node*)

B)Node* creare_Nod(candidati *c)
Funcție generală pentru a crea un nod. Se aloca dinamic memorie pentru campurile din "candidati", iar mai apoi se fixeaza pointerul stang și cel drept cu "NULL", returnând nodul nou. o(1)

C)Node* insert_lord(Node *node, float exp, candidati *q)
Funcție folosită pentru a insera candidatul cu statutul social "LORD" intr-un arbore binar de cautare în funcție de experiența acestuia. Dacă este singur este returnat sub forma de nod si alocat de funcția "creare_Nod", iar dacă experiența candidatului este mai mare decat cea a nodului curent este trimis in dreapta, iar dacă este mai mică este trimis in stanga. O(h)

D)Node* insert_av_cav(Node *node1, float exp1, candidati *q1)
Funcție folosită pentru a insera candidatul cu statutul social "AVENTURIER" sau "CAVALER" intr-un arbore binar de cautare în funcție de experiența acestuia. Dacă este singur este returnat sub forma de nod si alocat de funcția "creare_Nod", iar dacă experiența candidatului este mai mare decat cea a nodului curent este trimis in dreapta, iar dacă este mai mică este trimis in stanga. O(h)

E)void DeQueue(Queue *q, Node **BST_L, Node **BST_A_C)
Funcție folosită pentru a crea arborii cu proprietarea specifică. Se folosesc trei variabile auxiliare pentru a reține informatii specifice, urmand sa fie comparate cu anumite proprietati pentru a incadra corespunzator candidatul in BST-ul repartizat, folosindu-ne de funcțiile "insert_lord" și "insert_av_cav". O(h)

F)void scriere_BST_Lorzi(Node *root, FILE *f)
Funcție recursiva de scriere a candidaților de tip "LORD" in fișierul dat printr-un parametru: "test_2_lorzi.csv" in ordine descrescatoare in funcție de experienta. O(n)

G)void scriere_BST_C_A(Node *root, FILE *f)
Funcție recursiva de scriere a candidaților de tip "AVENTURIER" si "CAVALER" in fișierul dat printr-un parametru: "test_2_cavaleri_aventurieri.csv" in ordine descrescatoare in funcție de experienta. O(n)

H)void scriere_fisier(Node *BST_L, Node *BST_A_C)
Funcție de apelare a funcțiilor recursive de scriere in fișierele dorite cu tot cu primul rând necesar și inchiderea fișierelor deschise. O(n)

I)void elibereaza_BST(Node *root)
Funcție generală de eliberare a memoriei alocate dinamic specifică arborelui. Aceasta este recursiva folosind metoda "postordine". O(n)

J)Node *minNode(Node *node)
Funcție generală pentru a afla care este nodul cu cea mai mica experienta din arbore, returnând-ul. O(h)

K)Node *deleteNode(Node *root, char *nume, float exp)
Funcție folosită pentru ștergerea unui nod din BST folosind experiența și numele drept criterii, gestionând toate cazurile de existență a copiilor posibile. Aceasta caută recursiv dupa experiența, avand trei cazuri: cand este frunza - elibereaza nodul si returneaza "NULL"; cand are un singur copil - elibereaza memoria pentru nodul curent si îl inlocuieste cu copilul acestuia, returnând nodul; cand are doi copii - se cauta succesorul cu metoda "inordine" folosind functia "minNode", se face o copie profunda a datelor din nod in nodul temporar(folosind-ul ca nod principal in urmatoarea cautare) și apoi se șterge recursiv succesorul, returnând nodul la final. O(h)

L)void prelucrareContestatii(Node **BST_L)
Funcție de citire a contestațiilor. Aceasta citește fiecare linie din fișier si prelucreaza datele folosind alte variabile temporare, pe care le foloseste in funcția "deleteNode" pentru a șterge nodul specific și inchide fisierul deschis. O(m*h)


2. temapa2.c/temapa2.h

A)Structura Traseu
i. numele traseului (char)
ii. experienta acordata in urma parcurgerii pădurilor (int)
iii. numărul pădurilor parcurse (int)

B)Structura Participant
i. numele participantului ce este asignat pentru un traseu (char)
ii. experienta participantului (float)
iii. o variabilă de tip "Traseu" care reține informatii despre traseul asignat participantului 

C)Structura Heap
i. o variabila de tip "Participant" ce conține informatii despre participant
ii. marimea heap-ului (int)
iii. capacitatea heap-ului (int)

D)Heap* create_Heap(int capacitate)
Funcție generala pentru a crea heap-ul dorit, alocand dinamic memorie pentru toate campurile necesare, urmand sa returnam heap-ul creat. O(1)

E)void extragere_traseu(Traseu *vec, char *nume_fisier)
Funcție folosită pentru a prelucra datele despre trasee, urmand sa distribuie datele specifice unui vector de tip "Traseu". Aceasta funcție extrage numele din fișier, extrage experiența acordată si o copiaza in vectorul specific si numără cate paduri exista pentru acel traseu, apoi inchide fisierul. O(n*m)

F)void resize(Heap *h)
Funție generala folosita pentru a schimba capacitatea(o măreste dublu), realocând memoria necesara unui alt vector de tip "Participant" pentru a nu pierde datele dinainte de marire, copiem in heap-ul principal vectorul realocat. O(n)

G)void extragere_max(Node *BST, Node **BST_top, int *i)
Funcție de extragere a primilor patru participanti(folosit si pentru tipul "LORD", cat si pentru tipul "AVENTURIER" sau/și "CAVALER"), construind un alt BST cu candidații respectivi. O(n)

H)void insert_Heap(Heap **h, Participant p)
Funcție generala folosita pentru a insera variabile de tip "Participant" in heap-ul creat anterior. Acesta verifica daca heap-ul a ajuns la capacitatea maxima, daca da apeleaza funcția "resize", face o copie a mărimii și o incrementeaza cu încă o unitate ulterior. Verifica condiția de existență a participantului in heap pentru a putea să fie valabilă condiția inițiala, formand heap-ul dorit. O(n)

I)Participant creare_Lord(Node **top, Traseu *trasee, int i)
Funcție folosită pentru a crea o variabilă "Participant" eligibilă de tip "LORD", inițializand numele, experiența si traseul specific, returnând variabila. O(1)

J)Participant creare_Aventurier_Cavaler(Node **top, Traseu *trasee, int i)
Funcție folosită pentru a crea o variabilă "Participant" eligibilă de tip "AVENTURIER" sau/și "CAVALER", inițializand numele, experiența si traseul specific, returnând variabila. O(1)

K)void scrie_Heap(Heap **h, char* numeFisier)
Funcție de scriere in fisierul "test_4.csv" a heap-ului creat anterior și inchizând fisierul deschis. O(n) - n este marimea heap-ului.

L)Heap* actualizare_exp(Heap *h, Traseu *trasee)
Funcție de actualizare a unui heap creat in funcție cu experiența acumulată de participanți trecând prin padurile asignate(adunându-se cu cea inițiala), sortând participanții si inserându-i folosind funcția "insert_Heap", returnând heap-ul creat. O(n)

M)void swap(Participant* a, Participant* b)
Funcție generală pentru a interschimba doua variabile de tip "Participant". O(1)

N)void premiere(Heap *h)
Funcție folosită pentru a scrie in fișierul "test_6.csv" informațiile primilor trei participanti in functie de experiența acumulata, eliberând memoria pentru heap-ul auxiliar si inchizând fisierul. O(1)

O)void eliberare_Heap(Heap **h)
Funcție generala pentru eliberarea memoriei alocate dinamic specifică heap-ului. O(1)

3. temapa3.c/temapa3.h

A)Structura Graf
i. numarul de varfuri (int)
ii. matricea specifica grafului (int **)
iii. vectorul de grade de iesire ale nodurilor (int)
iiii. vectorul de grade de intrare ale nodurilor (int)

B)Graf * alocGraph (int val)
Funcție generală de alocare dinamica a memoriei specifica grafului. O(n)

C)Graf* creare_Graf();
Funcție folosită pentru a crea graful corespunzator informatiilor din fisierul "drumuri.csv". O(n)

D)void grade_ies_int(Graf *g)
Funcție folosită pentru a calcula gradele de intrare si de iesire a nodurilor grafului. O(n^2)

E)void dfs(Graf *g, int *vizitat, int *drum, int nr, int i, int *nr_curent, FILE *f)
Funcție folosită pentru a genera traseele cu conditia ca sa inceapa cu un nod care are gradul de intrare 0 si sa se termine cu un nod care are gradul de iesire 0. Aceasta foloseste un vector care tine evidenta nodurilor vizitate, un vector pentru a tine informatiile despre drumul parcurs pana la nodul cu gradul de iesire 0, atunci cand ajungem la un vector cu aceasta conditie scriem in fisierul reponsabil drumul specific pana la acel nod, o variabila care tine evidenta pozitiilor in vectorul "drum", o variabila pentru nodul in sine, o variabila pentru a stii la ce traseu suntem si fisierul deschis in main si inchis tot in main, folosit pentru a scrie soluția. Este o functie recursiva, folosindu-ne de "vizitat[i]=0" evităm situațiile in care repetăm nodul cu gradul de iesire 0 deja scris. O(n)

F)void elibereazaGraf(Graf* graf)
Funcție folosită pentru a elibera memoria alocata dinamic specifica grafului. O(n)