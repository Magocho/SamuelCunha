#ifndef DEFINICOES_H_INCLUDED
#define DEFINICOES_H_INCLUDED

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

/*
- MAKESPAN
- GERENCIAR OS CROMOSSOMOS
- ROLETA DE SELEÇÃO
- CRÍTERIOS DE AVALIAÇÃO
- RESULTADO
-
    T1 T2 T3 5 8 9 10 6 11 5 6 15
M0  5 8 9
M1  10 6 11
M2  5 6 15


123

MO 5  8 9
M1 10 16 27
M2 15 22 42

213

MO 8 5
M1
M2


Array
123 -> 42

123 -> 6 -> 35%
231 -> 54 -> 15%
213 -> 4 -> 50%

213  x 231 ->
*/
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

void aloca_tarefa(cabeca_tarefa* pInicio, int n);



#endif // DEFINICOES_H_INCLUDED
