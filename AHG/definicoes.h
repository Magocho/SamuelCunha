#ifndef DEFINICOES_H_INCLUDED
#define DEFINICOES_H_INCLUDED

 // A intenção é declarar tudo aqui! (Talvez seja um péssima ideia 04/11)
// E depois chamar só uma vez no main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <assert.h> // Para ERROS graves!

#define QUANTIDADE_TAREFA 2 // Pela definição SÓ vamos receber 2 tarefas!
#define NAO_TEM_FITNESS_AINDA -7 // Por conveniência
#define FILHOS_POR_CROSSOVER 2 // Por conveniência
/*

*/

//********* ISSO NÃO FUNCIONA! ***********
/*
typedef struct matriz{
    int valor;
    struct matriz* linha;
    struct matriz* coluna;
} elemento_matriz;

typedef struct cabeca_matriz1{
    elemento_matriz* sequencia;
    struct cabeca_matriz1* prox;
    int indice;
} cabeca_tarefa;

typedef struct cabeca_matriz2{
    elemento_matriz* sequencia;
    struct cabeca_matriz2* prox;
    int indice;
} cabeca_maquina;
*/
//************** DECORAÇÃO! ********************* cansei de ver só texto branco...
// para mais cores: https://gist.github.com/avelino/3188137
#define VERMELHO "\033[0;31m"
#define BRANCO "\033[1;37m"
#define ROXO "\033[0;35m"
#define VERDE "\033[0;32m"

typedef struct matriz{
    struct matriz* prox_tarefa; // aponta para próxima tarefa
    int id_tarefa;             // TALVEZ SEJA REDUNDANTE
    int* pMaquina;            // ponteiro para um ARRAY
} Tarefa_Matriz;

typedef struct{
    Tarefa_Matriz* fila_tarefa;
    int total_de_maquina;
    int total_de_tarefa;
} Cabecca_Matriz;

typedef struct cromossomos{ // PROVISÓRIO -------> MUDAR MUITO!
    int fitness; // TCC makespan
    double porcentagem; // Para a roleta
    int* genes;
} individuo;

typedef struct grupo{
    individuo** individuo;
    double soma_dos_fitness;
    int qtde_de_individuo;
    int qtde_de_individuo_ocupado;
    int qtde_de_tarefas; //redundante talvez;
    individuo* darwin_boy;
    bool precisa_ordenar;
} populacCao;

//************** MAKESPAN.C ********************* para mais detalhes veja os .c
Tarefa_Matriz* cria_matriz_Maquina_Tarefa(int numero_maquina, int numero_tarefa); // Aloca o espaço para a matriz de acordo com as máquinas
bool coloca_tempo_tarefa(Cabecca_Matriz** Matriz, int* fila_tarefa, int qtde_tarefa, int indice_MAQ); // Versão para mais tarefas
int makespan_de_uma_sequencia(int* seq_tarefa, int** matriz_suporte, Cabecca_Matriz** Matriz); // Acho que funciona bem

void imprime_matriz_TESTE(Cabecca_Matriz** Matriz); // Isso é para testes.

//************** CROMOSSOMOS.C *********************
individuo* cria_aleatoriamente(int numero_de_tarefas);
individuo** cruzamento(individuo* pai, individuo* mae, int numero_de_tarefa);
void mutacCao(individuo* teste, int numero_de_tarefa);
void mata_alguem(individuo* quem_quero_matar);

void imprime_individo_TESTE(individuo* teste, int numero_de_tarefa);

//************** ROLETA_VIDA.C *********************
populacCao* cria_populacCao_inicial(int qtde_da_amostra_inicial, int qtde_tarefa, Cabecca_Matriz** mMatriz, int** auxiliar);
bool ciclo_populacCao(populacCao* amostra, Cabecca_Matriz** mMatriz, int** auxiliar);
void THANOS_tinha_razao(populacCao* amostra);
void AO_JAIRO_COM_LOVE(populacCao* amostra);
bool ANDAR_COM_FE_VOU_POIS_NAO_COSTUMA_FAIAR(populacCao* amostra);
void ordenador(populacCao* amostra);

void calcula_porcentagem_TESTE(individuo* novo);
void imprime_tudo_TESTE(populacCao* amostra);
#endif // DEFINICOES_H_INCLUDED
