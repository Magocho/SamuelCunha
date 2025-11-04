#include "definicoes.h"


void cria_tarefa(cabeca_tarefa* atual, int n){
    atual->prox = malloc(sizeof(cabeca_tarefa));
    atual->sequencia = NULL;
    atual->indice = n;
}

void aloca_tarefa(cabeca_tarefa* pInicio, int n){
    int i;
    cabeca_tarefa* aux = pInicio;
    pInicio = malloc(sizeof(cabeca_tarefa));
    pInicio->indice = 0;
    pInicio->prox = NULL;
    pInicio->sequencia = NULL;
    for(i = 1; i < n; i++){
        cria_tarefa(aux, i);
        printf("criou um %d", i);
    }
    return;
}




