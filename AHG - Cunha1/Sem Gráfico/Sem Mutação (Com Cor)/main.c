#include "definicoes.h"

int main(){

    srand(time(NULL));
    bool pode_ir = false;
    char char_resposta;
    int num_populacCao_inicial;
    int num_geracCoes;

    titulo();
    Cabecca_Matriz* mMatriz = malloc(sizeof(Cabecca_Matriz));

    assert(ler_instancia(retorna_instancia(menu_de_selecao()), &mMatriz));

    printf("\n\t> Quer comecar o algoritmo genetico ["VERDE"S"CINZA"/"VERMELHO"N"CINZA"]:\n\t> "VERDE);
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
        };

///*****************************************************************************************************************************************
        clock_t fim = clock();

        printf("\n   +--------------------- RESULTADO ---------------------+\n");
        printf("\t> Melhor:"AMARELO" %d "CINZA"s (Makespan)\n", tribo->darwin_boy->fitness);
        printf("\t> Tempo:"ROXO"  %lf "CINZA"s\n", (double) (fim - inicio) / CLOCKS_PER_SEC);
        printf("\t> "VERMELHO"DNA ");
        imprime_individo_TESTE(tribo->darwin_boy, mMatriz->total_de_tarefa);
        printf(CINZA"   +-----------------------------------------------------+\n");

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
        else printf(CINZA"\n\t>> Uma pena que nao quis tentar...\n");
    }

    return 0;
}
