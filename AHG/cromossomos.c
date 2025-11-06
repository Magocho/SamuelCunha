#include "definicoes.h"

/*
    Aqui se tem as funções para criar um indivíduo aleatoriamente, sua reprodução e mutação.

    A reprodução de indivíduo (ESQUEMA)

        [1, 2, 3, 4, 5]                       (Utilizando um intervalo fixo de 3)
            X               => (novo filho) - [1, 2, 4, 3 ,5]
        [5, 2, 1, 4, 3]                       [5, 2, 4, 1 ,3]

    Q1: Incesto é um problema? -----------> É UM PROBLEMA, PODE ENTRAR EM LOOP INFINITO
        R1.1: Acredito que não, se definirmos o intervalo de mutação mais amplo.
        R1.2: Mas, na intenção de manter a viabilidade disso não perdermos o proposito da reprodução?
            R1.2.1: Acho que sim... Daí é fácil sortear os valores mesmo...

    Q2: Qual o melhor intervalo para fazer cross-over?
        R2.1: Metade? Na natureza é assim acho...
        R2.2: E aleatório? - Sei lá, como implementar isso daí...

    Q3: Qual a diferença disso e do bingo?
        R3.1: Nós achamos que sabemos o que está acontecendo em um...
*/

void shuffle(int* sequencia, int num_tarefa){ // Veja a função cria_aleatoriamente para um contexto maior!
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

individuo* cria_aleatoriamente(int numero_de_tarefas){  // DISCUTIR ESSA FUNÇÃO! NÃO GOSTEI MUITO DELA, MAS NÃO CONSEGUI PENSAR EM ALGO MELHOR.
                                                       // Talvez usat bit...
                                                      //Pensei em alguns nomes melhores: ASSIM_ZARATUSTRA_DISSE ou melhor ASSIM_SAMUEL_QUIS ou CUNHA_NO_BARRO
    individuo* novo = malloc(sizeof(individuo));     // P.S. achei um solução elegante, neste site:
                                                    // https://benpfaff.org/writings/clc/shuffle.html
    novo->genes = malloc(numero_de_tarefas * sizeof(int));
    novo->fitness = NAO_TEM_FITNESS_AINDA;

    assert(novo != NULL); // Tomara que isso nunca aconteça.

    int i;
    for(i = 0; i < numero_de_tarefas; i++)
        novo->genes[i] = i;

    shuffle(novo->genes, numero_de_tarefas);

    return novo;
}



void confirma_crossover(individuo* novo, int lim_inferior, int lim_superior, int num_tarefa){ // Isso deu trabalho...
    int i, j, ref;
    //int soma = 0;
    int suporte[num_tarefa];

    // QUARTA TENTATIVA -> Não sei qual é melhor...

    for(i = 0; i < num_tarefa; i++)
        suporte[i] = 0;

    for(i = 0; i < num_tarefa; i++)
        suporte[novo->genes[i]]++;

    for(i = lim_inferior; i < lim_superior; i++){
        ref = novo->genes[i];

        if(suporte[ref] > 0){
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

    // A PRIMEIRA NÃO FUNCIONOU

    // A SEGUNDA FICOU MUITO, MUITO GRANDE...

    /* TERCEIRA TENTATIVA
    for(i = 0; i < num_tarefa; i++)
        suporte[i] = i;

    for(j = 0; j < num_tarefa; j++){
        for(i = 0; i < num_tarefa; i++){
            if(suporte[j] == novo->genes[i])
                soma++;
        }

        switch(soma){
        case 1:
            suporte[j] = -1; // Apareceu uma vez (ok)
            break;
        case 0:
            suporte[j] = -2; // Apareceu nenhuma vez (precisa colocar)
            break;
        default:
            suporte[j] = -1 * (1 + soma) ; // Apareceu mais de uma vez (ferrou)
            break;
        }

        soma = 0;
    }

    for(i = lim_inferior; i < lim_superior; i++){
        ref = novo->genes[i];
        if(suporte[ref] == -1)
            continue;

        if(suporte[ref] <= -3){
            for(j = 0; j < num_tarefa; j++){
                if(suporte[j] == -2){
                    novo->genes[i] = j;
                    suporte[j] = -1;
                    suporte[ref]++;
                    break;
                }
            }
        }
    }
    */
}


individuo* cruzamento(individuo* pai, individuo* mae, int numero_de_tarefa){ // Mudar isso, pensar numa forma melhor de passar o número de tarefa

    individuo* filhos = malloc(FILHOS_POR_CROSSOVER * sizeof(individuo));

    assert(filhos != NULL);

    //********************************************************* ---> Isso só permite dois filhos por cruzamento...
    filhos[0].genes = malloc(numero_de_tarefa * sizeof(int));
    filhos[1].genes = malloc(numero_de_tarefa * sizeof(int));
    //*********************************************************

    int lim_superior = rand() % numero_de_tarefa;
    int lim_inferior = rand() % numero_de_tarefa;
    int i;


    if(lim_inferior > lim_superior){
        i = lim_superior;
        lim_superior = lim_inferior;
        lim_inferior = i;
    }

    if(lim_inferior == lim_superior){
        if(lim_superior + 1 == numero_de_tarefa)
            lim_inferior--;
        else lim_superior++;
    }


    for(i = 0; i < lim_inferior; i++){
        filhos[0].genes[i] = pai->genes[i];
        filhos[1].genes[i] = mae->genes[i];
    }

    for(i = lim_inferior; i < lim_superior; i++){
        filhos[0].genes[i] = mae->genes[i];
        filhos[1].genes[i] = pai->genes[i];
    }

    for(i = lim_superior; i < numero_de_tarefa; i++){
        filhos[0].genes[i] = pai->genes[i];
        filhos[1].genes[i] = mae->genes[i];
    }

    confirma_crossover(&filhos[0], lim_inferior, lim_superior, numero_de_tarefa);
    confirma_crossover(&filhos[1], lim_inferior, lim_superior, numero_de_tarefa);

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

void imprime_individo_TESTE(individuo* teste, int numero_de_tarefa){
    int i;
    printf(BRANCO"\t> ");
    for(i = 0; i < numero_de_tarefa; i++){
        printf(VERDE"%d | ", teste->genes[i]);
    }
    printf(BRANCO"\n");
}
