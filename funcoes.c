#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

/*
Função aloca uma nova célula na memória, essa célula recebe o número da página única.
*/
celula *aloca(int i){
  celula *nova;
  nova =(celula*)malloc(sizeof(celula));
  if(nova == NULL){
    printf("Erro ao realizar alocação");
    exit(1);
  }
  nova->n = i;
  nova->prox = NULL;
  return nova;
}

/*
Função aloca uma nova célula na memória caso a definindo o início da lista caso seja vazia(NULL), caso contrário novas células serão encadeadas nas posições seguintes.
*/
void insereLista(int i, celula**lst){
  celula *pt;
  if(*lst==NULL){
    *lst = aloca(i);
  }else{
    pt = *lst;
    if(pt->prox == NULL){
      pt->prox = aloca(i);
    }else{
      while(pt->prox!=NULL){
        pt = pt->prox;
      }
      pt->prox = aloca(i);
    }
  }
}

/*
Função verifica se já existem elementos na lista, caso um elemento já esteja na lista retorna 1, caso contrário 0.
*/
int verificaQuadros(celula **lst, int i){
  celula *pt = *lst;
  if(pt != NULL){
    while(pt != NULL){
      if(pt->n == i){
        return 1;
      }
      pt=pt->prox;
    }
  }
  return 0;
}

/*
Percorre a lista e exibe os elementos contidos.
Utilizada para exibir o Frames no terminal.
*/
void printaLista(celula **lst){
  celula *pt = *lst;
  while(pt!=NULL){
    printf("%d\t",pt->n);
    pt=pt->prox;
  }
}


/*
Função recebe por parâmetro o vetor com as sequência de palavras, quantidade de Frames, número de paginas requeridas.
Percorrerá todo o vetor realizando a inserção e alteração de palavras na lista de Frames
A cada inserção ou alteração na lista uma falha de página é identificada e armazenada.
A cada iteração é exibido os valores armazenos na lista de Frames.
Por fim é exibido a quantidade de falhas de página.
*/
void FIFO(int V[],int qtdQuadros,int paginasreq){
  int falhas=0,contador=0,quadrosOcupados=0;
  celula *lstFifo=NULL,*quadroAtualizar=NULL,*aux;
  printf("---------\n");
  while(contador < paginasreq){
    if(verificaQuadros(&lstFifo,V[contador]) == 0 && quadrosOcupados < qtdQuadros){
      insereLista(V[contador],&lstFifo);
      printaLista(&lstFifo);
      quadrosOcupados++;
      falhas++;
      aux = lstFifo;
    }else{
      if(verificaQuadros(&lstFifo,V[contador]) == 0){
        aux->n = V[contador];
        aux = aux->prox;
        if(aux == NULL){
          aux = lstFifo;
        }
        falhas++;
        printaLista(&lstFifo);
      }
    }
    printf("\n");
    contador++;
  }
  printf("---------\n");
  printf("Falhas - FIFO | %d |\n",falhas);
}

/*
Função aloca uma nova célula na memória, essa célula recebe o número da página única e time=0 para iniciar a contagem de tempo que está na lista de Frames.
*/
celulaLru *alocaLRU(int i){
  celulaLru *nova;
  nova =(celulaLru*)malloc(sizeof(celulaLru));
  if(nova == NULL){
    printf("Erro ao realizar alocação");
    exit(1);
  }
  nova->n = i;
  nova->time=0;
  nova->prox = NULL;
  return nova;
}

/*
Função aloca uma nova célula na memória caso a definindo o início da lista caso seja vazia(NULL), caso contrário novas células serão encadeadas nas posições seguintes.
*/
void insereListaLRU(int i, celulaLru**lst){
  celulaLru *pt;
  if(*lst==NULL){
    *lst = alocaLRU(i);
  }else{
    pt = *lst;
    if(pt->prox == NULL){
      pt->prox = alocaLRU(i);
    }else{
      while(pt->prox!=NULL){
        pt = pt->prox;
      }
      pt->prox = alocaLRU(i);
    }
  }
}

/*
Função verifica se já existem elementos na lista, caso um elemento já esteja na lista retorna 1 e reinicia o tempo do elemento, caso contrário 0.
*/
int verificaQuadrosLRU(celulaLru **lst, int i){
  celulaLru *pt = *lst;
  if(pt != NULL){
    while(pt != NULL){
      if(pt->n == i){
        pt->time = 0;
        return 1;
      }
      pt=pt->prox;
    }
  }
  return 0;
}

/*
Percorre a lista e exibe os elementos contidos.
Utilizada para exibir o Frames no terminal.
*/
void printaListaLRU(celulaLru **lst){
  celulaLru *pt = *lst;
  while(pt!=NULL){
    printf("%d\t",pt->n);
    pt=pt->prox;
  }
}

/*
A cada iteração da função LRU o tempo dos elementos na lista de Frames é incrementado.
*/
void incrementaTime(celulaLru **lst){
  celulaLru *pt;
  pt = *lst;
  while(pt!=NULL){
    pt->time = pt->time+1;
    pt = pt->prox;
  }
}

/*
Caso seja necessário atualizar a lista de frames, a função selecionará o elemento que não é utilizado a mais tempo.
*/
void trocarMaiorTempo(celulaLru **lst,int i){
  celulaLru *pt,*maiorTempo;
  pt=*lst;
  maiorTempo=*lst;
  while(pt!=NULL){
    if(pt->time > maiorTempo->time){
      maiorTempo = pt;
    }
    pt = pt->prox;
  }
  maiorTempo->time = 0;
  maiorTempo->n = i;
}

/*
Função recebe por parâmetro o vetor com as sequência de palavras, quantidade de Frames, número de paginas requeridas.
Percorrerá todo o vetor realizando a inserção e alteração de palavras na lista de Frames de acordo com as condições de tempo.
A cada inserção ou alteração na lista uma falha de página é identificada e armazenada.
A cada iteração é exibido os valores armazenos na lista de Frames e o incremento do tempo dos elementos na lista de Frames.
Por fim é exibido a quantidade de falhas de página.
*/
void LRU(int V[],int qtdQuadros, int paginareq){
  int falhas=0,contador=0,quadrosOcupados=0;
  celulaLru *lstLRU=NULL;
    printf("---------\n");
  while(contador < paginareq){
    if(verificaQuadrosLRU(&lstLRU,V[contador]) == 0 && quadrosOcupados < qtdQuadros){
      insereListaLRU(V[contador],&lstLRU);
      quadrosOcupados++;
      falhas++;
      printaListaLRU(&lstLRU);
    }else{
      if(verificaQuadrosLRU(&lstLRU,V[contador]) == 0){
        trocarMaiorTempo(&lstLRU,V[contador]);
        falhas++;
        printaListaLRU(&lstLRU);
      }
    }
    contador++;
    incrementaTime(&lstLRU);
    printf("\n");
  }
  printf("---------\n");
  printf("Falhas - LRU | %d |\n",falhas);
}
