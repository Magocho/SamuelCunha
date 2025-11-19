#ifndef DEFINICOES_H_INCLUDED
#define DEFINICOES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <assert.h>

#define FILHOS_POR_CROSSOVER 2
#define MAX_LINHA 512
#define MAX_NOME 64

typedef struct matriz{
    struct matriz* prox_tarefa;
    int id_tarefa;
    int* pMaquina;
} Tarefa_Matriz;

typedef struct{
    Tarefa_Matriz* fila_tarefa;
    int total_de_maquina;
    int total_de_tarefa;
} Cabecca_Matriz;

typedef struct cromossomos{
    int fitness;
    double porcentagem;
    int* genes;
} individuo;

typedef struct grupo{
    individuo** individuo;
    double soma_dos_fitness;
    int qtde_de_individuo;
    int qtde_de_individuo_ocupado;
    int qtde_de_tarefas;
    individuo* darwin_boy;
} populacCao;

//************** MAKESPAN.C ********************* para mais detalhes veja os .c
Tarefa_Matriz* cria_matriz_Maquina_Tarefa(int numero_maquina, int numero_tarefa);
bool coloca_tempo_tarefa(Cabecca_Matriz** Matriz, int* fila_tarefa, int qtde_tarefa, int indice_MAQ);
int makespan_de_uma_sequencia(int* seq_tarefa, int** matriz_suporte, Cabecca_Matriz** Matriz);
void libera_Matriz_toda(Cabecca_Matriz** Matriz);

//************** CROMOSSOMOS.C *********************
individuo* cria_aleatoriamente(int numero_de_tarefas);
individuo** cruzamento(individuo* pai, individuo* mae, int numero_de_tarefa);
void mutacCao(individuo* teste, int numero_de_tarefa);
void mata_alguem(individuo* quem_quero_matar);

//************** ROLETA_VIDA.C *********************
populacCao* cria_populacCao_inicial(int qtde_da_amostra_inicial, int qtde_tarefa, Cabecca_Matriz** mMatriz, int** auxiliar);
bool ciclo_populacCao(populacCao* amostra, Cabecca_Matriz** mMatriz, int** auxiliar);
void reduz_pela_metade_populacCao(populacCao* amostra);
void libera_TODA_populacCao(populacCao* amostra);
bool atualiza_o_melhor_encontrado(populacCao* amostra);
void ordenador(populacCao* amostra);
void normaliza_porcentagem(populacCao* amostra);

//************* LEITOR_TXT.C ***********************
int menu_de_selecao();
char* retorna_instancia(int num);
bool ler_instancia(char* caso, Cabecca_Matriz** mMatriz);
int determinar_dados_populacCao(bool eh_amostra_inicial);
void titulo();

//************** DEBUG.C / TESTE ************************************
void imprime_matriz_TESTE(Cabecca_Matriz** Matriz);
void calcula_porcentagem_TESTE(individuo* novo);
void imprime_individo_TESTE(individuo* teste, int numero_de_tarefa);
void imprime_tudo_TESTE(populacCao* amostra);
void debug_TESTE();

#endif // DEFINICOES_H_INCLUDED
