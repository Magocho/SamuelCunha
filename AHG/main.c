#include "definicoes.h"

int main(){
    int tarefa1, tarefa2, qtd_MAQ, i = 0; // Alguma coisa aqui é lixo não sei o que...

    Cabecca_Matriz* mMatriz = malloc(sizeof(mMatriz));

    printf("Pequeno algoritmo genetico que nao funciona!\n");

    printf("\tInsira quantidade de Maq.:\n\t> ");

    while(scanf("%d", &mMatriz->total_de_maquina)!=1 || mMatriz->total_de_maquina <= 0){
        printf(VERMELHO"\tERRO: quantidade de maquinas invalidos, tente outra vez!\n\t"BRANCO"> ");
        while(getchar() != '\n');
    }

    mMatriz->fila_tarefa = cria_matriz_Maquina_Tarefa(mMatriz->total_de_maquina, QUANTIDADE_TAREFA); // obs. ISSO SÓ FUNCIONA COM 2 TAREFAS!
    mMatriz->total_de_tarefa = QUANTIDADE_TAREFA;

    int* aux_matriz = malloc(sizeof(int) * (QUANTIDADE_TAREFA * mMatriz->total_de_maquina)); // Com certeza existe ideias melhores, mas burro que sou pensei nisso...

    printf("\tInsira valores de tempo [t1, t2]\n\t> "ROXO);

    //*********************************************************** ISSO AS VEZES TEIMA DE QUERER FALHAR, NÃO SEI O MOTIVO... CULPA DO DOUGLAS.
    qtd_MAQ = mMatriz->total_de_maquina;
    do{
        if(scanf(" %d %d", &tarefa1, &tarefa2) == 2 && tarefa1 > 0 && tarefa2 > 0){ //AHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
                                                                                   // VOU
            assert(coloca_tempo_tarefa(&mMatriz, tarefa1, tarefa2, i));
            i++;
            if(i < qtd_MAQ)
                printf(BRANCO"\t> "ROXO);
        }else{
            printf(VERMELHO"\tERRO: valores invalidos, tente outra vez!\n"BRANCO"\t> "ROXO);
        }
    }while(i < qtd_MAQ);
    //***********************************************************

    // Testes
    int seq1[2] = {0, 1};
    int seq2[2] = {1, 0};
    imprime_matriz_TESTE(&mMatriz);
    printf("\n> Seq1: %d\n> Seq2: %d", makespan_de_uma_sequencia(seq1, &aux_matriz, &mMatriz),makespan_de_uma_sequencia(seq2, &aux_matriz, &mMatriz));

    return 0;
}
