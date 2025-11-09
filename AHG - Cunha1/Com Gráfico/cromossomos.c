#include "definicoes.h"

/*
    Aqui se tem as funções para criar um indivíduo aleatoriamente, sua reprodução e mutação.

    A reprodução de indivíduo (ESQUEMA)

        [1, 2, 3, 4, 5]                       (Utilizando um intervalo fixo de 3)
            X               => (novo filho) - [1, 2, 4, 3 ,5]
        [5, 2, 1, 4, 3]                       [5, 2, 4, 1 ,3]

    obs. função shuffle adaptado de:
        https://benpfaff.org/writings/clc/shuffle.html
*/

void shuffle(int* sequencia, int num_tarefa){
    if(num_tarefa > 1){
        int i, j, aux;
        for(i = 0; i < num_tarefa - 1; i++){
            j = i + rand() / (RAND_MAX / (num_tarefa - i) + 1);
            aux = sequencia[j];
            sequencia[j] = sequencia[i];
            sequencia[i] = aux;
        }
    }
}

individuo* cria_aleatoriamente(int numero_de_tarefas){

    individuo* novo = malloc(sizeof(individuo));

    novo->genes = malloc(numero_de_tarefas * sizeof(int));
    novo->fitness = 0;
    novo->porcentagem = 0.0;

    assert(novo != NULL);

    int i;
    for(i = 0; i < numero_de_tarefas; i++)
        novo->genes[i] = i;

    shuffle(novo->genes, numero_de_tarefas);

    return novo;
}

void confirma_crossover(individuo* novo, int lim_inferior, int lim_superior, int num_tarefa){
    int i, j, ref;
    int suporte[num_tarefa];

    for(i = 0; i < num_tarefa; i++)
        suporte[i] = 0;

    for(i = 0; i < num_tarefa; i++)
        suporte[novo->genes[i]]++;

    for(i = lim_inferior; i < lim_superior; i++){
        ref = novo->genes[i];

        if(suporte[ref] > 1){
            for(j = 0; j < num_tarefa; j++){
                if(suporte[j] == 0){
                    novo->genes[i] = j;
                    suporte[j] = 1;
                    suporte[ref]--;
                    break;
                }
            }
        }
    }
}

individuo** cruzamento(individuo* pai, individuo* mae, int numero_de_tarefa){

    individuo** filhos = malloc(FILHOS_POR_CROSSOVER * sizeof(individuo*));

    assert(pai != NULL && mae != NULL);
    assert(filhos != NULL);

    int i;

    for(i = 0; i < FILHOS_POR_CROSSOVER; i++){
        filhos[i] = malloc(sizeof(individuo));
        assert(filhos[i] != NULL);
        filhos[i]->genes = malloc(numero_de_tarefa * sizeof(int));
        assert(filhos[i]->genes != NULL);
    }

    int lim_superior = rand() % numero_de_tarefa;
    int lim_inferior = rand() % numero_de_tarefa;

    if(lim_inferior > lim_superior){
        i = lim_superior;
        lim_superior = lim_inferior;
        lim_inferior = i;
    }

    if(lim_inferior == lim_superior){
        if(lim_superior < numero_de_tarefa - 1){
            lim_superior++;
        }
        else if(lim_inferior > 0){
            lim_inferior--;
        }
    }

    for(i = 0; i < lim_inferior; i++){
        filhos[0]->genes[i] = pai->genes[i];
        filhos[1]->genes[i] = mae->genes[i];
    }

    for(i = lim_inferior; i < lim_superior; i++){
        filhos[0]->genes[i] = mae->genes[i];
        filhos[1]->genes[i] = pai->genes[i];
    }

    for(i = lim_superior; i < numero_de_tarefa; i++){
        filhos[0]->genes[i] = pai->genes[i];
        filhos[1]->genes[i] = mae->genes[i];
    }

    confirma_crossover(filhos[0], lim_inferior, lim_superior, numero_de_tarefa);
    confirma_crossover(filhos[1], lim_inferior, lim_superior, numero_de_tarefa);

    return filhos;
}

void mutacCao(individuo* teste, int numero_de_tarefa){
    int mutante_UM = rand() % numero_de_tarefa;
    int mutante_DOIS = rand() % numero_de_tarefa;

    if(mutante_UM == mutante_DOIS){
        if(mutante_UM + 1 == numero_de_tarefa)
            mutante_DOIS--;
        else mutante_UM++;
    }

    int aux = teste->genes[mutante_UM];
    teste->genes[mutante_UM] = teste->genes[mutante_DOIS];
    teste->genes[mutante_DOIS] = aux;
}

void mata_alguem(individuo* quem_quero_matar){
    free(quem_quero_matar->genes);
    free(quem_quero_matar);
}

void imprime_individo_TESTE(individuo* teste, int numero_de_tarefa){
    int i;
    printf(BRANCO"| ");
    for(i = 0; i < numero_de_tarefa; i++){
        printf(BRANCO"%d"CINZA" | ", teste->genes[i]);
    }
    printf(BRANCO"\n");
}
