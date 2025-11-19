#include "definicoes.h"

int main(){

    srand(time(NULL));
    bool pode_ir = false;
    char char_resposta;
    int num_populacCao_inicial;
    int num_geracCoes;
    int sortudo = 1;

    titulo();
    Cabecca_Matriz* mMatriz = malloc(sizeof(Cabecca_Matriz));

    assert(ler_instancia(retorna_instancia(menu_de_selecao()), &mMatriz));

    printf("\n\t> Quer comecar o algoritmo genetico [ S / N ]:\n\t> ");
    scanf(" %c", &char_resposta);

    if(char_resposta == 'S' || char_resposta == 's'){
        pode_ir = true;
        num_populacCao_inicial = determinar_dados_populacCao(true);
        num_geracCoes = determinar_dados_populacCao(false);
    }

    if(pode_ir){

        int* aux_matriz = malloc(sizeof(int) * (mMatriz->total_de_tarefa * mMatriz->total_de_maquina));

        clock_t inicio = clock();
///******************************************************* ALGORITMO GENETICO **********************************************************

        populacCao* tribo = cria_populacCao_inicial(num_populacCao_inicial, mMatriz->total_de_tarefa, &mMatriz, &aux_matriz);
        ordenador(tribo);

        int n = 0;
        while(n < num_geracCoes){
            if(!ciclo_populacCao(tribo, &mMatriz, &aux_matriz)){
                atualiza_o_melhor_encontrado(tribo);
                reduz_pela_metade_populacCao(tribo);
                n++;
            }

            if(rand() % 1000 == 0){
                sortudo = rand() % tribo->qtde_de_individuo_ocupado;
                mutacCao(tribo->individuo[sortudo], tribo->qtde_de_tarefas);
                tribo->individuo[sortudo]->fitness = makespan_de_uma_sequencia(tribo->individuo[sortudo]->genes, &aux_matriz, &mMatriz);
                normaliza_porcentagem(tribo);
                ordenador(tribo);
            }
        };

///*****************************************************************************************************************************************
        clock_t fim = clock();

        printf("\n   +--------------------- RESULTADO ---------------------+\n");
        printf("\t> Melhor: %d s (Makespan)\n", tribo->darwin_boy->fitness);
        printf("\t> Tempo:  %lf s\n", (double) (fim - inicio) / CLOCKS_PER_SEC);
        printf("\t> DNA ");
        imprime_individo_TESTE(tribo->darwin_boy, mMatriz->total_de_tarefa);
        printf("   +-----------------------------------------------------+\n");

        libera_TODA_populacCao(tribo);
        free(aux_matriz);
        libera_Matriz_toda(&mMatriz);
    }
    else{
        libera_Matriz_toda(&mMatriz);
        if(char_resposta == 'D' || char_resposta == 'd'){
            system("cls");
            debug_TESTE();
        }
        else printf("\n\t>> Uma pena que nao quis tentar...\n");
    }

     // obs. Caso o progama não apresente os resultados, descomente a linha abaixo:
    // getchar(); getchar();
    return 0;
}
