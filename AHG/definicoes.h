#ifndef DEFINICOES_H_INCLUDED
#define DEFINICOES_H_INCLUDED

 // A intenção é declarar tudo aqui! (Talvez seja um péssima ideia 04/11)
// E depois chamar só uma vez no main.c

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <assert.h> // Para ERROS graves!

#define QUANTIDADE_TAREFA 2 // Pela definição SÓ vamos receber 2 tarefas!
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

typedef struct{ // PROVISÓRIO -------> MUDAR MUITO!
    int fitness;
    int* genes;
} Hernando_e_familia;

//************** MAKESPAN.C ********************* para mais detalhes veja o makespan.c
Tarefa_Matriz* cria_matriz_Maquina_Tarefa(int numero_maquina, int numero_tarefa); // Aloca o espaço para a matriz de acordo com as máquinas
bool coloca_tempo_tarefa(Cabecca_Matriz** Matriz, int tarefaUM, int tarefaDOIS, int indice_MAQ); // Meio ruim, mas funciona
int makespan_de_uma_sequencia(int* seq_tarefa, int** matriz_suporte, Cabecca_Matriz** Matriz); // Acho que funciona bem

void imprime_matriz_TESTE(Cabecca_Matriz** Matriz); // Isso é para testes.



#endif // DEFINICOES_H_INCLUDED
