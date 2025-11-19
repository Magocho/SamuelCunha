#include "definicoes.h"
/*
    Roleta da vida:
    -> Definidor da população inicial;
    -> Opção de definir o limite máximo da população;
    -> Ordenador da população;
    -> Decide quem reproduz;

    ESQUEMA:

    Individuo       [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, ... , n ]
    Makespan        [ 20, 21, 32, 43, 44, 45, 56, 57, 78, 89, ... , n ]
    Porcentagem (%) [ 50%, 10%, 9%, 8%, 5%, ...]

    obs. porcentagem = 1 / (1 + makespan)

    IDEIA GERAL (Do nosso algoritmo):

        1. cria_populacCao_inicial
            1.a. ordenador

        2. ciclo_populacCao
            2.a. (TRUE)  atualiza_o_melhor_encontrado
            2.b. (FALSE) reduz_pela_metade_populacCao

        3. "Utilizar condições no main.c"
            3.a. (TRUE)  vá para 2.
            3.b. (FALSE) continue

        4. libera_TODA_populacCao

    obs.
    [1]. implementação do qsort foi adaptado de:
        https://en.wikipedia.org/wiki/Qsort

    [2]. a comparação foi inspirada de:
        https://stackoverflow.com/questions/9120065/best-way-to-compare-two-int-arrays-of-the-same-length
*/
void imprime_tudo_TESTE(populacCao* amostra){
    int i;
    printf("\n   +----------------------- CICLO -----------------------+\n");
    printf("\t[DEBUG] Amostra: ai %d, aio %d, at %d, soma %lf\n", amostra->qtde_de_individuo, amostra->qtde_de_individuo_ocupado, amostra->qtde_de_tarefas, amostra->soma_dos_fitness);
    for(i = 0; i < amostra->qtde_de_individuo_ocupado; i++){
        printf("\tporcentagem %lf | fitness %d ", amostra->individuo[i]->porcentagem, amostra->individuo[i]->fitness);
        imprime_individo_TESTE(amostra->individuo[i], amostra->qtde_de_tarefas);
    }
}

void calcula_porcentagem_TESTE(individuo* novo){
    assert(novo != NULL);
    assert(novo->fitness > 0);
    novo->porcentagem = 1.0 /(1.0 + novo->fitness);
}

void calcula_porcentagem(individuo* novo){
    assert(novo != NULL);
    assert(novo->fitness > 0);
    novo->porcentagem = 1.0 /(1.0 + novo->fitness);
}

void normaliza_porcentagem(populacCao* amostra){
    amostra->soma_dos_fitness = 0.0;
    int i;
    for(i = 0; i < amostra->qtde_de_individuo_ocupado; i++){
        assert(amostra->individuo[i] != NULL);
        calcula_porcentagem(amostra->individuo[i]);
        amostra->soma_dos_fitness += amostra->individuo[i]->porcentagem;
    }

    for(i = 0; i < amostra->qtde_de_individuo_ocupado; i++)
        amostra->individuo[i]->porcentagem = (amostra->individuo[i]->porcentagem / amostra->soma_dos_fitness) * 100;
}

void soma_fitness(populacCao* amostra){
    int i;
    amostra->soma_dos_fitness = 0.0;
    for(i = 0; i < amostra->qtde_de_individuo_ocupado; i++){
        assert(amostra->individuo[i] != NULL);
        amostra->soma_dos_fitness += amostra->individuo[i]->fitness;
    }
}

populacCao* cria_populacCao_inicial(int qtde_da_amostra_inicial, int qtde_tarefa, Cabecca_Matriz** mMatriz, int** auxiliar){
    populacCao* novo = malloc(sizeof(populacCao));
    novo->qtde_de_tarefas = qtde_tarefa;
    novo->qtde_de_individuo = 2 * qtde_da_amostra_inicial;
    novo->qtde_de_individuo_ocupado = qtde_da_amostra_inicial;
    novo->soma_dos_fitness = 0.0;
    novo->darwin_boy = NULL;
    novo->individuo = malloc(sizeof(individuo*) * (novo->qtde_de_individuo));
    int i;
    for(i = 0; i < novo->qtde_de_individuo; i++){
        novo->individuo[i] = cria_aleatoriamente(novo->qtde_de_tarefas);
        novo->individuo[i]->fitness = makespan_de_uma_sequencia(novo->individuo[i]->genes, auxiliar, mMatriz);
    }

    for(i = novo->qtde_de_individuo_ocupado; i < novo->qtde_de_individuo; i++)
        novo->individuo[i] = NULL;

    normaliza_porcentagem(novo);
    return novo;
}

int compara_individuo(const void* p, const void* q){
    const individuo* primeiro = *(const individuo**)p;
    const individuo* segundo  = *(const individuo**)q;

    if(primeiro->fitness < segundo->fitness){
        return -1;
    }else if(primeiro->fitness > segundo->fitness) {
        return 1;
    }else{
        return 0;
    }
}

void ordenador(populacCao* amostra){
    qsort(amostra->individuo, amostra->qtde_de_individuo_ocupado, sizeof(individuo*), compara_individuo);
}

individuo* roleta_vida(populacCao* amostra){
    double sortudo = ((double)rand() / RAND_MAX) * 100.0;
    double soma = 0;
    int i;
    for(i = 0; i < amostra->qtde_de_individuo_ocupado; i++){
        assert(amostra->individuo[i] != NULL);
        soma += amostra->individuo[i]->porcentagem;
        if(sortudo <= soma)
            return amostra->individuo[i];
    }
    return amostra->individuo[0];
}

bool insere_na_populacCao(populacCao* amostra, individuo* filho){

    assert(filho != NULL);
    if(amostra->qtde_de_individuo_ocupado >= amostra->qtde_de_individuo)
        return false;

    int i, j, k = amostra->qtde_de_individuo_ocupado;

    for(i = 0; i < amostra->qtde_de_individuo_ocupado; i++){
        if(memcmp(filho->genes, amostra->individuo[i]->genes, (sizeof(int)* amostra->qtde_de_tarefas)) == 0)
            return true;

        if(filho->fitness < amostra->individuo[i]->fitness){
            k = i;
            break;
        }
    }

    for(j = amostra->qtde_de_individuo_ocupado; j > k; j--)
        amostra->individuo[j] = amostra->individuo[j - 1];

    amostra->individuo[k] = filho;
    amostra->qtde_de_individuo_ocupado++;

    return true;
}

bool ciclo_populacCao(populacCao* amostra, Cabecca_Matriz** mMatriz, int** auxiliar){

    if(amostra->qtde_de_individuo_ocupado >= amostra->qtde_de_individuo){
        return false;
    }
    int ref = amostra->qtde_de_individuo_ocupado;

    individuo** novos = cruzamento(roleta_vida(amostra), roleta_vida(amostra), (*mMatriz)->total_de_tarefa);
    assert(novos != NULL);
    novos[0]->fitness = makespan_de_uma_sequencia(novos[0]->genes, auxiliar, mMatriz);

    novos[1]->fitness = makespan_de_uma_sequencia(novos[1]->genes, auxiliar, mMatriz);

    if(!insere_na_populacCao(amostra, novos[0])){
        return false;
    }

    if(!insere_na_populacCao(amostra, novos[1])){
        return false;
    }

    if(amostra->qtde_de_individuo_ocupado > ref)
        normaliza_porcentagem(amostra);

    return true;
}

void reduz_pela_metade_populacCao(populacCao* amostra){
    int i;
    individuo* morto;
    for(i = amostra->qtde_de_individuo / 2; i < amostra->qtde_de_individuo; i++){
        morto = amostra->individuo[i];
        amostra->individuo[i] = NULL;
        mata_alguem(morto);
    }
    amostra->qtde_de_individuo_ocupado = amostra->qtde_de_individuo / 2;
}

void libera_TODA_populacCao(populacCao* amostra){
    int i;
    individuo* pai_do_jairo;
    for(i = 0; i < amostra->qtde_de_individuo_ocupado; i++){
        pai_do_jairo = amostra->individuo[i];
        amostra->individuo[i] = NULL;
        mata_alguem(pai_do_jairo);
    }
    free(amostra->individuo);
}

bool atualiza_o_melhor_encontrado(populacCao* amostra){

    if(amostra == NULL || amostra->qtde_de_individuo_ocupado == 0)
        return false;

    if(amostra->darwin_boy == NULL)
        amostra->darwin_boy = amostra->individuo[0];

    if (amostra->darwin_boy->genes != NULL && amostra->individuo[0]->genes != NULL)
        if(memcmp(amostra->darwin_boy->genes, amostra->individuo[0]->genes, (sizeof(int)* amostra->qtde_de_tarefas)) == 0)
            return false;

    amostra->darwin_boy = amostra->individuo[0];
    return true;
}
