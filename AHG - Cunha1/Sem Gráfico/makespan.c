#include "definicoes.h"

 // Versão com array: (ESQUEMA)
// obs. desenho feito com: https://asciiflow.com/#/
/*
    Cabecca_Matriz
    +---------------+             M_Tarefa         M_Tarefa
    |               |           +-----------+    +-----------+
    |  qtd_MAQ      |           |  id 0     |    |  id 0     |
    |               |           |           |    |           |
    |  Fila Tarefa -+----------->  prox  ---+---->  prox  ---+-----> NULL
    |               |           |           |    |           |
    |               |           |  pMaquina |    |  pMaquina |
    +---------------+           |     |     |    |     |     |
                                +-----+-----+    +-----+-----+
                                      |                |
                                      |                |
                                      v                v
                                MAQ  +-+              +-+
                                [0]  |1|  ----------  |9|
                                [1]  |3|  ----------  |7|
                                [2]  |4|  ----------  |6|
                                 .   |5|              |8|
                                 .   |6|              |5|
                                 .   |8|              |7|
                                     |.|              |.|
                                     |.|              |.|
                                     |.|              |.|
                                     +-+              +-+
 */
// Isso lida com matriz e calculo de makespan.

int max(int a, int b){
    return a > b ? a : b;
}

void libera_Matriz_toda(Cabecca_Matriz** Matriz){
    if(Matriz == NULL || *Matriz == NULL)
        return;

    Tarefa_Matriz* ref = (*Matriz)->fila_tarefa;
    Tarefa_Matriz* prox;

    while(ref != NULL){
        prox = ref->prox_tarefa;
        free(ref->pMaquina);
        free(ref);
        ref = prox;
    }

    free(*Matriz);
    *Matriz = NULL;
}

Tarefa_Matriz* cria_tarefa(int numero_maquina, int id_tarefa){

    Tarefa_Matriz* novo = malloc(sizeof(Tarefa_Matriz));
    assert(novo != NULL);
    novo->id_tarefa = id_tarefa;
    novo->pMaquina = calloc(numero_maquina, sizeof(int));
    novo->prox_tarefa = NULL;
    return novo;
}

Tarefa_Matriz* cria_matriz_Maquina_Tarefa(int numero_maquina, int numero_tarefa){
    int i;
    assert(numero_maquina > 0);
    Tarefa_Matriz* primeiro = cria_tarefa(numero_maquina, 0);
    Tarefa_Matriz* aux = primeiro;
    for(i = 1; i < numero_tarefa; i++){
        aux->prox_tarefa = cria_tarefa(numero_maquina, i);
        aux = aux->prox_tarefa;
    }
    return primeiro;
}

bool coloca_tempo_tarefa(Cabecca_Matriz** Matriz, int* fila_tarefa, int qtde_tarefa, int indice_MAQ){
    Tarefa_Matriz* aux = (*Matriz)->fila_tarefa;
    if(indice_MAQ >= (*Matriz)->total_de_maquina)
        return false;

    int i;
    for(i = 0; i < qtde_tarefa; i++){
        assert(aux != NULL);
        aux->pMaquina[indice_MAQ] = fila_tarefa[i];
        aux = aux->prox_tarefa;
    }
    return true;
}

int retorna_valor_da_matriz(Tarefa_Matriz* comecCo, int linha, int coluna){
    Tarefa_Matriz* ref = comecCo;
    while(ref != NULL && ref->id_tarefa != coluna)
        ref = ref->prox_tarefa;

    assert(ref != NULL);

    return ref->pMaquina[linha];
}

int index_matriz(int i, int j, int quantidade_tarefa){
    return i * quantidade_tarefa + j;
}

int makespan_de_uma_sequencia(int* seq_tarefa, int** matriz_suporte, Cabecca_Matriz** Matriz){
    int* suporte = *matriz_suporte;
    Tarefa_Matriz* aux = (*Matriz)->fila_tarefa;
    int TT = (*Matriz)->total_de_tarefa;
    int i, j;
    for(i = 0; i < (*Matriz)->total_de_maquina; i++)
        suporte[index_matriz(i, 0, TT)] = retorna_valor_da_matriz(aux, i, seq_tarefa[0]);

    for(i = 1; i < (*Matriz)->total_de_tarefa; i++)
        suporte[index_matriz(0, i, TT)] = retorna_valor_da_matriz(aux, 0, seq_tarefa[i]) + suporte[index_matriz(0, i - 1, TT)];

    for(i = 1; i < (*Matriz)->total_de_maquina; i++){
        for(j = 1; j < (*Matriz)->total_de_tarefa; j++){
            suporte[index_matriz(i, j, TT)] = retorna_valor_da_matriz(aux, i, seq_tarefa[j]) + max(suporte[index_matriz(i - 1, j, TT)], suporte[index_matriz(i, j - 1, TT)]);
        }
    }
    return suporte[index_matriz(i - 1, j - 1, TT)];
}

void imprime_matriz_TESTE(Cabecca_Matriz** Matriz){
    Tarefa_Matriz* aux = (*Matriz)->fila_tarefa;
    Tarefa_Matriz* ref;
    int i;
    for(i = 0; i < (*Matriz)->total_de_maquina; i++){
        printf(BRANCO"\n\t");
        ref = aux;
        while(ref != NULL){
            printf(BRANCO"%d ", ref->pMaquina[i]);
            ref = ref->prox_tarefa;
        }
    }
    printf(BRANCO"\n");
}
