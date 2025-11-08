#include "definicoes.h"

int main(){
    srand(time(NULL));
    int tarefa, qtd_MAQ, i = 0, j =0; // Alguma coisa aqui é lixo não sei o que...
    bool debug;
    char debug_resposta;

    Cabecca_Matriz* mMatriz = malloc(sizeof(mMatriz));

    printf("Pequeno algoritmo genetico que nao funciona!\n");

    printf("\tQuer entrar em DEBUG [S / N]:\n\t> ");
    scanf(" %c", &debug_resposta);

    if(debug_resposta == 'S' || debug_resposta == 's')
        debug = true;

    if(debug){
        printf("----------------------- VAI DAR RUIM -----------------------------+");
        printf("\n\tInsira quantidade de Maq.:\n\t> ");

        while(scanf("%d", &mMatriz->total_de_maquina)!=1 || mMatriz->total_de_maquina <= 0){
            printf(VERMELHO"\tERRO: quantidade de maquinas invalidos, tente outra vez!\n\t"BRANCO"> ");
            while(getchar() != '\n');
        }

        printf("\n\tInsira quantidade de Tarefa.:\n\t> ");
        while(scanf("%d", &mMatriz->total_de_tarefa)!=1 || mMatriz->total_de_tarefa <= 0){
            printf(VERMELHO"\tERRO: quantidade de maquinas invalidos, tente outra vez!\n\t"BRANCO"> ");
            while(getchar() != '\n');
        }

        mMatriz->fila_tarefa = cria_matriz_Maquina_Tarefa(mMatriz->total_de_maquina, mMatriz->total_de_tarefa); // obs. ISSO SÓ FUNCIONA COM 2 TAREFAS!

        int* aux_matriz = malloc(sizeof(int) * (mMatriz->total_de_tarefa * mMatriz->total_de_maquina)); // Com certeza existe ideias melhores, mas burro que sou pensei nisso...

        int fila_temp_tarefa[mMatriz->total_de_tarefa];

        printf("\tInsira valores de tempo [t]\n\t> "ROXO);

        //*********************************************************** ISSO AS VEZES TEIMA DE QUERER FALHAR, NÃO SEI O MOTIVO... CULPA DO DOUGLAS.
        qtd_MAQ = mMatriz->total_de_maquina;
        do{
            if(scanf(" %d", &tarefa) == 1 && tarefa > 0){ //AHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
                fila_temp_tarefa[j] = tarefa;
                j++;
                if(j == mMatriz->total_de_tarefa){
                    assert(coloca_tempo_tarefa(&mMatriz, fila_temp_tarefa, mMatriz->total_de_tarefa, i));
                    i++;
                    j = 0;
                }
                if(i < qtd_MAQ)
                    printf(BRANCO"\t> "ROXO);
            }else{
                j = 0;
                printf(VERMELHO"\tERRO: valores invalidos, tente outra vez!\n"BRANCO"\t> "ROXO);
            }
        }while(i < qtd_MAQ);
        //***********************************************************

        // Testes
        imprime_matriz_TESTE(&mMatriz);

        populacCao* tribo = cria_populacCao_inicial(25, mMatriz->total_de_tarefa, &mMatriz, &aux_matriz);
        ordenador(tribo);
        imprime_tudo_TESTE(tribo);

        int n = 0;
        while(n < 3){
            if(ciclo_populacCao(tribo, &mMatriz, &aux_matriz)){
                printf("FOi");
                imprime_tudo_TESTE(tribo);
                //continue;
            }
            else{
                ANDAR_COM_FE_VOU_POIS_NAO_COSTUMA_FAIAR(tribo);
                THANOS_tinha_razao(tribo);
                n++;
            }
        };
        imprime_tudo_TESTE(tribo);

        printf("----------------------- DEU CERTO? -----------------------------+\n");
        imprime_individo_TESTE(tribo->darwin_boy, mMatriz->total_de_tarefa);

        //assert(tribo->darwin_boy != NULL);
        printf("\t> Melhor: %d\n" , tribo->darwin_boy->fitness);

        AO_JAIRO_COM_LOVE(tribo);

        /*
        imprime_matriz_TESTE(&mMatriz); // funcionou não sei o por que...
        int ahahaha = 7;
        individuo* teste[ahahaha];
        int k = 0;
        double soma = 0;
        for(k = 0; k < ahahaha; k++){
                teste[k] = cria_aleatoriamente(mMatriz->total_de_tarefa);
                imprime_individo_TESTE(teste[k], mMatriz->total_de_tarefa);
                teste[k]->fitness = makespan_de_uma_sequencia(teste[k]->genes, &aux_matriz, &mMatriz);
                printf("\t> Seq%d: %d\n", k, teste[k]->fitness);
                calcula_porcentagem(teste[k]);
                printf("\t> %lf%%\n", teste[k]->porcentagem);
                soma += teste[k]->porcentagem;

        }

        //normaliza_porcentagem(&teste, ahahaha);

        for(k = 0; k < ahahaha; k++){
                printf("\t> %lf%%\n", teste[k]->porcentagem);
                soma += teste[k]->porcentagem;
        }

        printf("\t>final %lf%%\n", soma);

        individuo* teste1 = cria_aleatoriamente(mMatriz->total_de_tarefa);
        individuo* teste2 = cria_aleatoriamente(mMatriz->total_de_tarefa);
        imprime_individo_TESTE(teste1, mMatriz->total_de_tarefa);
        imprime_individo_TESTE(teste2, mMatriz->total_de_tarefa);
        printf("\t> Seq1: %d\n\t> Seq2: %d\n", makespan_de_uma_sequencia(teste1->genes, &aux_matriz, &mMatriz),makespan_de_uma_sequencia(teste2->genes, &aux_matriz, &mMatriz));

        individuo* filhos = cruzamento(teste1, teste2, mMatriz->total_de_tarefa);

        imprime_individo_TESTE(&filhos[0], mMatriz->total_de_tarefa);
        imprime_individo_TESTE(&filhos[1], mMatriz->total_de_tarefa);
        printf("\t> Seq1x2: %d\n\t> Seq2x1: %d\n", makespan_de_uma_sequencia(teste1->genes, &aux_matriz, &mMatriz),makespan_de_uma_sequencia(teste2->genes, &aux_matriz, &mMatriz));

        mutacCao(&filhos[0], mMatriz->total_de_tarefa);
        mutacCao(&filhos[1], mMatriz->total_de_tarefa);
        imprime_individo_TESTE(&filhos[0], mMatriz->total_de_tarefa);
        imprime_individo_TESTE(&filhos[1], mMatriz->total_de_tarefa);
        printf("\t> Seq1x2M: %d\n\t> Seq2x1M: %d\n", makespan_de_uma_sequencia(teste1->genes, &aux_matriz, &mMatriz),makespan_de_uma_sequencia(teste2->genes, &aux_matriz, &mMatriz));
        */
    }

    else printf("\n\t>> Infelizmente ainda nao estah terminado o progama...\n\t\t obrigado por ler!\n");

    return 0;
}
