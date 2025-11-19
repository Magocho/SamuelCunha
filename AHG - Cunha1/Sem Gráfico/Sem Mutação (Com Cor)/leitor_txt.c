#include "definicoes.h"
/*
    O objetivo dessas funções são:
    > extrair um "instance" de flowshop1.txt
    > salvar em log, um registro da população
    > retornar para MAKESPAN.C os valores do "instance" escolhido.
    > e interface gráfica (decoração)

    obs.
        para a função bool ler_instancia() se utilizou da:

            def parse_all_flowshop_instances_from_text(text) retirada de:
                        https://colab.research.google.com/drive/1q3Q1r54_2FWWipCF93guvyZ-5nLSuJTE?usp=sharing#scrollTo=DRDaaGh4YRwY

            Que foi "traduzida para C" com a ajuda de:
                https://www.codeconvert.ai/python-to-c-converter?id=1af21585-4757-45e1-9cee-bb774435d5fc

            P.S. não tenho muita confiaça nela, todo o projeto foi construido para inserção manual... Então, com certeza há uma forma mais inteligente de a implementar.
*/

char* retorna_instancia(int num){
    char* caso;
    switch(num){
    case 1:
        caso = "car1";
        break;
    case 2:
        caso = "car2";
        break;
    case 3:
        caso = "car3";
        break;
    case 4:
        caso = "car4";
        break;
    case 5:
        caso = "car5";
        break;
    case 6:
        caso = "car6";
        break;
    case 7:
        caso = "car7";
        break;
    case 8:
        caso = "car8";
        break;
    case 9:
        caso = "hel1";
        break;
    case 10:
        caso = "hel2";
        break;
    case 11:
        caso = "reC01";
        break;
    case 12:
        caso = "reC03";
        break;
    case 13:
        caso = "reC05";
        break;
    case 14:
        caso = "reC07";
        break;
    case 15:
        caso = "reC09";
        break;
    case 16:
        caso = "reC11";
        break;
    case 17:
        caso = "reC13";
        break;
    case 18:
        caso = "reC15";
        break;
    case 19:
        caso = "reC17";
        break;
    case 20:
        caso = "reC19";
        break;
    case 21:
        caso = "reC21";
        break;
    case 22:
        caso = "reC23";
        break;
    case 23:
        caso = "reC25";
        break;
    case 24:
        caso = "reC27";
        break;
    case 25:
        caso = "reC29";
        break;
    case 26:
        caso = "reC31";
        break;
    case 27:
        caso = "reC33";
        break;
    case 28:
        caso = "reC35";
        break;
    case 29:
        caso = "reC37";
        break;
    case 30:
        caso = "reC39";
        break;
    default:
        caso = "reC41";
        break;
   }
   return caso;
}

bool menu_nome(int resposta){
    printf(CINZA"\t> Qual instancia deseja testar?\n");
    printf(CINZA"\t ["ROXO" 1 "CINZA"]"BRANCO" car\n");
    printf(CINZA"\t ["ROXO" 2 "CINZA"]"BRANCO" hel\n");
    printf(CINZA"\t ["ROXO" 3 "CINZA"]"BRANCO" reC\n");
    printf(CINZA"\t>> obs. Veja flowshop1.txt para mais detalhes.\n\t> "VERDE);

    if(resposta == 1 || resposta == 2 || resposta == 3)
        return false;
    else return true;
}

bool menu_tipo(int resposta){
    int i, j;
    switch(resposta){
    case -7:
        return false;
    case -1:
        printf(CINZA"\t> "AMARELO"* car *"CINZA" Qual tipo deseja testar?\n");
        for(i = 1; i < 9; i++){
            if(i == 1)
                printf(CINZA"\t ["ROXO" %d "CINZA"]"BRANCO" car%d (%d x %d)\n", i, i, 11, 5);
            else if(i == 2)
                printf(CINZA"\t ["ROXO" %d "CINZA"]"BRANCO" car%d (%d x %d)\n", i, i, 13, 4);
            else if(i == 3)
                printf(CINZA"\t ["ROXO" %d "CINZA"]"BRANCO" car%d (%d x %d)\n", i, i, 12, 5);
            else if(i == 4)
                printf(CINZA"\t ["ROXO" %d "CINZA"]"BRANCO" car%d (%d x %d)\n", i, i, 14, 4);
            else if(i == 5)
                printf(CINZA"\t ["ROXO" %d "CINZA"]"BRANCO" car%d (%d x %d)\n", i, i, 10, 6);
            else if(i == 6)
                printf(CINZA"\t ["ROXO" %d "CINZA"]"BRANCO" car%d (%d x %d)\n", i, i, 8, 9);
            else printf(CINZA"\t ["ROXO" %d "CINZA"]"BRANCO" car%d (%d x %d)\n", i, i, i, i);
        }
        if(resposta > 0 && resposta < 9)
            return false;
        break;
    case -2:
        printf(CINZA"\t> "AMARELO"* hel *"CINZA" Qual tipo deseja testar?\n");
        printf(CINZA"\t ["ROXO" %d "CINZA"]"BRANCO" hel%d (100 x 10)\n", 9, 1);
        printf(CINZA"\t ["ROXO" %d "CINZA"]"BRANCO" hel%d (20 x 10)\n", 10, 2);
        if(resposta > 8 && resposta < 11)
            return false;
        break;
    case -3:
        j = 11;
        printf(CINZA"\t> "AMARELO"* reC *"CINZA" Qual tipo deseja testar?\n");
        for(i = 1; i < 42; i = i + 2){
            if(i <= 5)
                printf(CINZA"\t ["ROXO" %d "CINZA"]"BRANCO" reC0%d (20 x 5)\n", j, i);
            else if(i <= 11)
                printf(CINZA"\t ["ROXO" %d "CINZA"]"BRANCO" reC%d (20 x 10)\n", j, i);
            else if(i <= 17)
                printf(CINZA"\t ["ROXO" %d "CINZA"]"BRANCO" reC%d (20 x 15)\n", j, i);
            else if(i <= 23)
                printf(CINZA"\t ["ROXO" %d "CINZA"]"BRANCO" reC%d (30 x 10)\n", j, i);
            else if(i <= 29)
                printf(CINZA"\t ["ROXO" %d "CINZA"]"BRANCO" reC%d (30 x 15)\n", j, i);
            else if(i <= 35)
                printf(CINZA"\t ["ROXO" %d "CINZA"]"BRANCO" reC%d (50 x 10)\n", j, i);
            else printf(CINZA"\t ["ROXO" %d "CINZA"]"BRANCO" reC%d (75 x 20)\n", j, i);

            j++;
        }
        if(resposta > 10 && resposta < 32)
            return false;
        break;
    }

    printf(CINZA"\t>> obs. Para voltar digite -7.\n\t> "VERDE);

    return true;
}

bool eh_valido_tipo(int escolha, int resposta){
    switch(escolha){
    case -7:
        return false;
    case -1:
        if(resposta > 0 && resposta < 9)
            return true;
        break;
    case -2:
        if(resposta > 8 && resposta < 11)
            return true;
        break;
    case -3:
        if(resposta > 10 && resposta < 32)
            return true;
        break;
    }

    return false;
}

bool le_inteiro(int* valor) {

    if(scanf(" %d", valor) == 1){
        getchar();
        return true;
    }

    getchar();
    return false;
}

int menu_de_selecao(){
    int resposta = -1, aux;
    bool deu_certo = false;

    while(!deu_certo){

        if(menu_nome(resposta)){
            if(!le_inteiro(&resposta)){
                system("cls");
                printf(VERMELHO"\t> ERRO: insira um valor valido!\n");
                continue;
            }
        }

        aux = resposta * -1;
        if(menu_tipo(aux)){
            if(!le_inteiro(&resposta)){
                system("cls");
                printf(VERMELHO"\t> ERRO: insira um valor valido!\n");
                continue;
            }
            deu_certo = eh_valido_tipo(aux, resposta);
        }

        if(resposta == -7){
            system("cls");
            continue;
        }

        if(!deu_certo){
            system("cls");
            printf(VERMELHO"\t> ERRO: insira um valor valido!\n");
        }
    }
    printf(CINZA);
    return resposta;
}

bool ler_instancia(char* caso, Cabecca_Matriz** mMatriz){

    char nome_arquivo[] = "flowshop1.txt";

    FILE *arq = fopen(nome_arquivo, "r");

    if(!arq)
        return false;

    char linha[MAX_LINHA];
    bool encontrou = false;
    int nTarefa = 0, nMaquina = 0;
    int i, j;

    while(fgets(linha, sizeof(linha), arq)){

        if(strncmp(linha, " instance", 9) == 0){
            char nome_atual[MAX_NOME];
            if(sscanf(linha, " instance %s", nome_atual) == 1 && strcmp(nome_atual, caso) == 0){
                printf("   +-----------------------------------------------------+\n");
                encontrou = true;
                printf(BRANCO"\t> Instancia:"AMARELO" %s "BRANCO"\n", caso);

                fgets(linha, sizeof(linha), arq);
                fgets(linha, sizeof(linha), arq);
                fgets(linha, sizeof(linha), arq);
                printf("\t> Descricao:"CINZA"%s", linha);

                if(!fgets(linha, sizeof(linha), arq)){
                    fclose(arq);
                    return false;
                }

                if(sscanf(linha, "%d %d", &nTarefa, &nMaquina) != 2){
                    fclose(arq);
                    return false;
                }

                printf(BRANCO"\t> Total de tarefas:"ROXO" %d "BRANCO"\n\t> Total de maquinas:"ROXO" %d\n\n"CINZA, nTarefa, nMaquina);

                assert(*mMatriz != NULL);
                (*mMatriz)->total_de_maquina = nMaquina;
                (*mMatriz)->total_de_tarefa = nTarefa;
                (*mMatriz)->fila_tarefa = cria_matriz_Maquina_Tarefa(nMaquina, nTarefa);

                int** tempos = malloc(nTarefa * sizeof(int*));
                assert(*tempos != NULL);

                for(i = 0; i < nTarefa; i++){
                    tempos[i] = malloc(nMaquina * sizeof(int));
                    assert(tempos[i] != NULL);
                    for(j = 0; j < nMaquina; j++)
                        tempos[i][j] = 0;
                }

                for(i = 0; i < nTarefa; i++){

                    assert(fgets(linha, sizeof(linha), arq));

                    char* token = strtok(linha, " \t\r\n");
                    while(token != NULL){
                        int maq = atoi(token);
                        token = strtok(NULL, " \t\r\n");
                        if(token == NULL)
                            break;
                        int tempo = atoi(token);

                        if(maq >= 0 && maq < nMaquina)
                            tempos[i][maq] = tempo;

                        token = strtok(NULL, " \t\r\n");
                    }
                }

                int *fila = malloc(nTarefa * sizeof(int));
                assert(fila != NULL);

                for(i = 0; i < nMaquina; i++){
                    for(j = 0; j < nTarefa; j++){
                        fila[j] = tempos[j][i];
                    }
                    assert(coloca_tempo_tarefa(mMatriz, fila, nTarefa, i));
                }

                for(i = 0; i < nTarefa; i++){
                    printf("\t|");
                    for(j = 0; j < nMaquina; j++){
                        printf("%4d ", tempos[i][j]);
                    }
                    printf(" |\n");
                }
                printf("   +-----------------------------------------------------+\n");
                free(fila);
                for(i = 0; i < nTarefa; i++)
                    free(tempos[i]);

                free(tempos);
                break;
            }
        }
    }

    assert(encontrou);

    fclose(arq);
    return encontrou;
}

int determinar_dados_populacCao(bool eh_amostra_inicial){
    int i = 0;
    printf(CINZA);
    if(eh_amostra_inicial){
        printf("\n\t> Diga o valor da populacao inicial:\n"AZUL"\t[IMPORTANTE]\n");
        printf(AZUL"\t> "CINZA"Note que se o valor escolhido:"AMARELO" N > N!"CINZA", teremos todos os valores ou ocuparemos toda a memoria!\n");
        printf(AZUL"\t> "CINZA"Para a reproducao ser valida:"AMARELO" N >= 2"CINZA", pois nao da para se cruzar sozinho!\n\t> "VERDE);
        while(i < 2){
            if(scanf(" %d", &i) != 1){
                printf(VERMELHO"\t> ERRO: insira um valor valido!\n"CINZA"\t> "VERDE);
                getchar();
            }
            else if(i < 2) printf(CINZA"\t> "VERDE);
        }
    }
    else{
        printf("\n\t> Diga quantas geracoes ocorrera:\n"AZUL"\t[IMPORTANTE]\n");
        printf(AZUL"\t> "CINZA"Note que se o valor escolhido for muito grande, demorara mais!\n");
        printf(AZUL"\t> "CINZA"Para ser valida:"AMARELO" N > 1"CINZA", pois se nao so se considera a geracao original!\n\t> "VERDE);
        while(i < 2){
            //printf(CINZA"\t> "VERDE);
            if(scanf(" %d", &i) != 1){
                printf(VERMELHO"\t> ERRO: insira um valor valido!\n"CINZA"\t> "VERDE);
                getchar();
            }
            else if(i < 2) printf(CINZA"\t> "VERDE);
        }
    }

    printf(CINZA);
    return i;
}

void titulo(){
    int i;
    printf("\t+");
    for(i = 0; i < 28; i++)
        printf("-");
    printf("+\n\t| Pequeno Algoritmo Genetico |\n\t+");
    for(i = 0; i < 28; i++)
        printf("-");
    printf("+\n");

    //printf("\tFeito por:\n\n");
}
