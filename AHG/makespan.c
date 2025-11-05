#include "definicoes.h"

//****************** ISSO NÃO FUNCIONA! ************
/*
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
*/
//************************************************

/// Versão com array: (O que tinha imaginado)
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

// Isso lida com matriz e calculo de makespan!

int max(int a, int b){
    return a > b ? a : b;
}

Tarefa_Matriz* cria_tarefa(int numero_maquina, int id_tarefa){

    Tarefa_Matriz* novo = malloc(sizeof(Tarefa_Matriz));
    assert(novo != NULL);   // Só por precaução -> Se der ruim, estamos muitos lascados.
    novo->id_tarefa = id_tarefa;
    novo->pMaquina = calloc(numero_maquina, sizeof(int));
    novo->prox_tarefa = NULL;
    return novo;
}

Tarefa_Matriz* cria_matriz_Maquina_Tarefa(int numero_maquina, int numero_tarefa){ // P.S. Pode ser adaptado para mais tarefas!
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

bool coloca_tempo_tarefa(Cabecca_Matriz** Matriz, int tarefaUM, int tarefaDOIS, int indice_MAQ){ // Não gostei dessa função, muita vagabundice nela...
    Tarefa_Matriz* aux = (*Matriz)->fila_tarefa;
    if(indice_MAQ >= (*Matriz)->total_de_maquina)
        return false;
    aux->pMaquina[indice_MAQ] = tarefaUM;
    aux->prox_tarefa->pMaquina[indice_MAQ] = tarefaDOIS;
    return true;
}

int retorna_valor_da_matriz(Tarefa_Matriz* comecCo, int linha, int coluna){ // Essa coisinha aqui assume que existe coluna 0 e linha 0
    Tarefa_Matriz* ref = comecCo;                                          // Se não, sabe lá o que acontece aqui...
    while(ref != NULL && ref->id_tarefa != coluna)
        ref = ref->prox_tarefa;

    assert(ref != NULL); // Se entrou aqui, sinceramente estamos NADANDO EM %#@#%! e existem 2 Edson no mundo...

    return ref->pMaquina[linha];
}

int index_matriz(int i, int j, int quantidade_tarefa){ // Minha melhor ideia em 04/11
    return i * quantidade_tarefa + j;
}

int makespan_de_uma_sequencia(int* seq_tarefa, int** matriz_suporte, Cabecca_Matriz** Matriz){ // TEnho minhas dúvidas ainda disso...
    int* suporte = *matriz_suporte;
    Tarefa_Matriz* aux = (*Matriz)->fila_tarefa;
    int TT = (*Matriz)->total_de_tarefa;
    int i, j;
    for(i = 0; i < (*Matriz)->total_de_maquina; i++)
        suporte[index_matriz(i, 0, TT)] = retorna_valor_da_matriz(aux, i, seq_tarefa[0]);

    for(i = 1; i < (*Matriz)->total_de_tarefa; i++)
        suporte[index_matriz(0, i, TT)] = retorna_valor_da_matriz(aux, 0, seq_tarefa[i]);

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
        while(ref != NULL){
            printf(BRANCO"%d ", ref->pMaquina[i]);
            ref = ref->prox_tarefa;
        }
        ref = aux;
    }
}
