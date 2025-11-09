#include "definicoes_SDL.h"

int main(){

    srand(time(NULL));
    bool pode_ir = false;
    char char_resposta;
    app_estado* novo = calloc(1, sizeof(app_estado));
    int num_populacCao_inicial;
    int num_geracCoes;
    bool graf_inicial = false;
    bool graf_final = false;
    bool graf_meio = false;

    titulo();
    Cabecca_Matriz* mMatriz = malloc(sizeof(Cabecca_Matriz));

    assert(ler_instancia(retorna_instancia(menu_de_selecao()), &mMatriz));

    printf("\n\t> Quer comecar o algoritmo genetico ["VERDE"S"CINZA"/"VERMELHO"N"CINZA"]:\n\t> "VERDE);
    scanf(" %c", &char_resposta);

    if(char_resposta == 'S' || char_resposta == 's'){
        pode_ir = true;
        num_populacCao_inicial = determinar_dados_populacCao(true);
        num_geracCoes = determinar_dados_populacCao(false);
        graf_inicial = determinar_grafico_SDL(1);
        graf_final = determinar_grafico_SDL(3);
        graf_meio = determinar_grafico_SDL(2);

    }

    if(pode_ir){

        int* aux_matriz = malloc(sizeof(int) * (mMatriz->total_de_tarefa * mMatriz->total_de_maquina));

        if(graf_inicial || graf_meio || graf_final)
            printf("\n   +----------------------- AVISO -----------------------+\n");

        clock_t inicio = clock();
///******************************************************* ALGORITMO GENETICO **********************************************************

        populacCao* tribo = cria_populacCao_inicial(num_populacCao_inicial, mMatriz->total_de_tarefa, &mMatriz, &aux_matriz);
        ordenador(tribo);

        if(graf_inicial){
            printf("\n\t>> "ROXO"[SDL3]"CINZA" Grafico da pop. "AMARELO"inicial"CINZA", aperte "AZUL"ESC"CINZA" para sair!\n");
            ciclo_SDL(novo, tribo);
        }

        int n = 0;
        while(n < num_geracCoes){
            if(!ciclo_populacCao(tribo, &mMatriz, &aux_matriz)){
                atualiza_o_melhor_encontrado(tribo);
                if(graf_meio){
                    printf("\n\t>> "ROXO"[SDL3]"CINZA" Grafico da pop. "AMARELO"%d"CINZA", aperte "AZUL"ESC"CINZA" para sair!\n", n);
                    ciclo_SDL(novo, tribo);
                }
                if(n != num_geracCoes - 1)
                    reduz_pela_metade_populacCao(tribo);
                n++;
            }
        };
///*****************************************************************************************************************************************
        clock_t fim = clock();

        if(graf_final){
            printf("\n\t>> "ROXO"[SDL3]"CINZA" Grafico da pop. "AMARELO"final"CINZA", aperte "AZUL"ESC"CINZA" para sair!\n");
            ciclo_SDL(novo, tribo);
        }

        printf("\n   +--------------------- RESULTADO ---------------------+\n");
        printf("\t> Melhor:"AMARELO" %d "CINZA"s (Makespan)\n", tribo->darwin_boy->fitness);
        printf("\t> Tempo:"ROXO"  %lf "CINZA"s\n", (double) (fim - inicio) / CLOCKS_PER_SEC);
        printf("\t> "VERMELHO"DNA ");
        imprime_individo_TESTE(tribo->darwin_boy, mMatriz->total_de_tarefa);
        printf(CINZA"   +-----------------------------------------------------+\n\t>> P.S. O tempo se utilizado o SDL, nao eh valido.\n");

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
