/*
Declaração das estuturas utilizadas e funções criadas.
*/

struct cel {
int n;
struct cel *prox;
};

struct celT {
int n;
int time;
struct celT *prox;
};

typedef struct cel celula;
typedef struct celT celulaLru;

celula *aloca(int i);
void insereLista(int i, celula**lst);
int verificaQuadros(celula **lst, int i);
void printaLista(celula **lst);
void FIFO(int V[],int qtdQuadros,int paginareq);

celulaLru *alocaLRU(int i);
void insereListaLRU(int i, celulaLru**lst);
int verificaQuadrosLRU(celulaLru **lst, int i);
void printaListaLRU(celulaLru **lst);
void incrementaTime(celulaLru **lst);
void trocarMaiorTempo(celulaLru **lst,int i);
void LRU(int V[],int qtdQuadros, int paginareq);
