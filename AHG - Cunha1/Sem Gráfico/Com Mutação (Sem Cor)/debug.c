#include "definicoes.h"
/*
    Aqui tem a versão anterior do programa:
        > Ele foi adaptado para servir como debug;
        > Também pode ser usado para inserir casos particulares;
        > Igualmente, serve como espaço isolado para testar novas funções sem problema.
*/
void debug_TESTE(){
    int tarefa, qtd_MAQ, i = 0, j =0;

    Cabecca_Matriz* mMatriz = malloc(sizeof(Cabecca_Matriz));

    printf("\n   +----------------------- DEBUG -----------------------+\n");
    printf("\t[AVISO]\n");
    printf("\t> Nao ha controle das insercoes, entao se pode facilmente cria situacoes impossiveis\n");

    printf("\n\t[DEBUG] Insira quantidade de Maq.:\n\t> ");
    while(scanf(" %d", &mMatriz->total_de_maquina)!=1 || mMatriz->total_de_maquina <= 0){
        printf("\t> ERRO: quantidade de maquinas invalidos, tente outra vez!\n\t> ");
        while(getchar() != '\n');
    }

    printf("\t[DEBUG] Insira quantidade de Tarefa.:\n\t> ");
    while(scanf(" %d", &mMatriz->total_de_tarefa)!=1 || mMatriz->total_de_tarefa <= 0){
        printf("\t> ERRO: quantidade de tarefas invalidos, tente outra vez!\n\t> ");
        while(getchar() != '\n');
    }

    mMatriz->fila_tarefa = cria_matriz_Maquina_Tarefa(mMatriz->total_de_maquina, mMatriz->total_de_tarefa);

    int* aux_matriz = malloc(sizeof(int) * (mMatriz->total_de_tarefa * mMatriz->total_de_maquina));

    int fila_temp_tarefa[mMatriz->total_de_tarefa];

    printf("\t[DEBUG] Insira valores de tempo [t]\n\t> ");

    qtd_MAQ = mMatriz->total_de_maquina;

    do{
        if(scanf(" %d", &tarefa) == 1 && tarefa > 0){
            fila_temp_tarefa[j] = tarefa;
            j++;
            if(j == mMatriz->total_de_tarefa){
                assert(coloca_tempo_tarefa(&mMatriz, fila_temp_tarefa, mMatriz->total_de_tarefa, i));
                i++;
                j = 0;
            }
            if(i < qtd_MAQ)
                printf("\t> ");
        }else{
            j = 0;
            printf("\tERRO: valores invalidos, tente outra vez!\n\t> ");
        }
    }while(i < qtd_MAQ);

        printf("\t[DEBUG] Matriz recebida");
        imprime_matriz_TESTE(&mMatriz);

        printf("\n\t[DEBUG] Insira valor da populacao inicial:\n\t> ");
        while(scanf(" %d", &i)!=1 || i <= 1){
            printf("\t> ERRO: quantidade de individuos invalida, tente outra vez!\n\t> ");
            while(getchar() != '\n');
        }

        printf("\n\t[DEBUG] Insira total de geracoes:\n\t> ");
        while(scanf(" %d", &j)!=1 || j <= 0){
            printf("\t> ERRO: quantidade de maquinas invalidos, tente outra vez!\n\t> ");
            while(getchar() != '\n');
        }

        printf("\n\t[DEBUG] Que a impressao de todas as geracoes? [1 -> SIM / 0 -> NAO]\n\t> ");
        while(scanf(" %d", &qtd_MAQ)!=1 || (qtd_MAQ != 0 && qtd_MAQ != 1)){
            printf("\t> ERRO: resposta invalida, tente outra vez!\n\t> ");
            while(getchar() != '\n');
        }

        populacCao* tribo = cria_populacCao_inicial(i, mMatriz->total_de_tarefa, &mMatriz, &aux_matriz);
        ordenador(tribo);

        imprime_tudo_TESTE(tribo);

        int n = 0;
//************************************** ALGORITMO GENETICO *******************************************************************
        while(n < j){
            if(!ciclo_populacCao(tribo, &mMatriz, &aux_matriz)){
                atualiza_o_melhor_encontrado(tribo);
                if(qtd_MAQ)
                    imprime_tudo_TESTE(tribo);
                reduz_pela_metade_populacCao(tribo);
                n++;
            }
        };
//*********************************************************************************************************
        imprime_tudo_TESTE(tribo);

        printf("\n----------------------- DEU CERTO? -----------------------------+\n");
        printf("\t> DNA ");
        imprime_individo_TESTE(tribo->darwin_boy, mMatriz->total_de_tarefa);
        printf("\t> Melhor: %d\n", tribo->darwin_boy->fitness);

        libera_TODA_populacCao(tribo);
        free(aux_matriz);
        libera_Matriz_toda(&mMatriz);
}
