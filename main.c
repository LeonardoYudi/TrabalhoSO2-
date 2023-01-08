*
Declaração das bibliotecas utilizadas. 
"biblitoca.h" possui as funções criadas para simular o gerenciamento de páginas.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"
#define  MAX 1000

/*
Main do programa, é declarado um vetor com as páginas unicas.
Após isso é lido a quantidade de quadros e o número de páginas requeridas.
São chamadas as funções FIFO E LRU.
*/
int main(void) {
  int v[MAX]={7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
  int quadros,paginasRequeridas;
  printf("Quantidade de Quadros:");
  scanf("%d",&quadros);
  printf("Quantidade de paginas Requeridas:");
  scanf("%d",&paginasRequeridas);
 
  FIFO(v,quadros,paginasRequeridas);
  LRU(v, quadros,paginasRequeridas);
  return 0;
}

