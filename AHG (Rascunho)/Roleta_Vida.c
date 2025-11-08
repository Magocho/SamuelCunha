#include "definicoes.h"

/*
    Roleta da vida...
    -> Definidor da população inicial
    -> Opção de definir o limite máximo da população
    -> Ordenador da população;
    -> Decide quem reproduz
    -> Determina do programa

    ESQUEMA:

    Individuo       [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, ... , n ]
    Makespan        [ 20, 21, 32, 43, 44, 45, 56, 57, 78, 89, ... , n ] --> Precisa estar ordenado!!!
    Porcentagem (%) [ 50%, 10%, 9%, 8%, 5%, ...]

    obs. porcentagem = 1 / (1 + makespan)

    Q1: Qual a definição da mutação?
        R1 Talvez uns 1%?
        R2Ela pode causar muito dano no progama...

    Quando ocupar n -> eliminar metade da população (TALVEZ)
*/
void imprime_tudo_TESTE(populacCao* amostra){
    int i;
    printf("Amostra: ai %d, aio %d, at %d, soma %lf\n", amostra->qtde_de_individuo, amostra->qtde_de_individuo_ocupado, amostra->qtde_de_tarefas, amostra->soma_dos_fitness);
    for(i = 0; i < amostra->qtde_de_individuo_ocupado; i++){
        imprime_individo_TESTE(amostra->individuo[i], amostra->qtde_de_tarefas);
        printf("porcentagem %lf | fitness %d\n", amostra->individuo[i]->porcentagem, amostra->individuo[i]->fitness);
    }
}

void calcula_porcentagem_TESTE(individuo* novo){
    assert(novo != NULL);
    assert(novo->fitness > 0);
    novo->porcentagem = 1.0 /(1.0 + novo->fitness);
}

void calcula_porcentagem(individuo* novo){
    assert(novo != NULL);                           /// Deu ruim aqui
    assert(novo->fitness > 0);                      // Deu certo agora
    novo->porcentagem = 1.0 /(1.0 + novo->fitness);
}

void normaliza_porcentagem(populacCao* amostra){
    amostra->soma_dos_fitness = 0.0;
    int i;
    for(i = 0; i < amostra->qtde_de_individuo_ocupado; i++){
        assert(amostra->individuo[i] != NULL);                  /// Deu ruim aqui
        calcula_porcentagem(amostra->individuo[i]);                // Deu certo
        amostra->soma_dos_fitness += amostra->individuo[i]->porcentagem;
    }

    for(i = 0; i < amostra->qtde_de_individuo_ocupado; i++)
        amostra->individuo[i]->porcentagem = (amostra->individuo[i]->porcentagem / amostra->soma_dos_fitness) * 100;
}

void soma_fitness(populacCao* amostra){
    int i;
    amostra->soma_dos_fitness = 0.0;                        // Esqueci o zero, mas agora vai
    for(i = 0; i < amostra->qtde_de_individuo_ocupado; i++){
        assert(amostra->individuo[i] != NULL);
        amostra->soma_dos_fitness += amostra->individuo[i]->fitness;
    }
}

populacCao* cria_populacCao_inicial(int qtde_da_amostra_inicial, int qtde_tarefa, Cabecca_Matriz** mMatriz, int** auxiliar){
    populacCao* novo = malloc(sizeof(populacCao));
    novo->precisa_ordenar = true;
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

    for(i = novo->qtde_de_individuo_ocupado; i < novo->qtde_de_individuo; i++) /// ALGUEM TEVE A BRILHANTE IDEIA DE NÃO COLOCAR NULL, NÃO VOU DIZER NOMES, MAS:
        novo->individuo[i] = NULL;                                                // L***** D**** L*** C** VOCê É MUITO CEGO

    normaliza_porcentagem(novo);
    return novo;
}

int compara_individuo(const void* p, const void* q){       // Isso copiei da https://en.wikipedia.org/wiki/Qsort
    const individuo* primeiro = *(const individuo**)p;    // Pensei em tentar fazer algo eficiente do zero
    const individuo* segundo  = *(const individuo**)q;   // Mas daí lembrei da aula do Sacchi sobre quicksort...
                                                        // E que alguém maís esperto já implementou em C...
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

individuo* roleta_vida(populacCao* amostra){    // Isso é macumba, não sei porque funciona...
    double sortudo = ((double)rand() / RAND_MAX) * 100.0;   // MAs funciona de alguma forma...
    double soma = 0;                                        // Não funciona mais
    int i;
    for(i = 0; i < amostra->qtde_de_individuo_ocupado; i++){
        assert(amostra->individuo[i] != NULL);                  //Funciona sim...
        soma += amostra->individuo[i]->porcentagem;
        if(sortudo <= soma)
            return amostra->individuo[i];
    }
    return amostra->individuo[0];
}

bool insere_na_populacCao(populacCao* amostra, individuo* filho){ // Muito engraçado, vocÊ foi a única função que não deu ERRO

    assert(filho != NULL);                                          // Não, minha funçãozinha, por que? Acreditava que eramos amigos... et tu insere_na_populacCao?
    if(amostra->qtde_de_individuo_ocupado >= amostra->qtde_de_individuo)    /// NÃO, INSERO NA TUA... (APUNHALADO PELAS COSTAS)
        return false;

    int i, j, k = amostra->qtde_de_individuo_ocupado;

    for(i = 0; i < amostra->qtde_de_individuo_ocupado; i++){
        if(memcmp(filho->genes, amostra->individuo[i]->genes, (sizeof(int)* amostra->qtde_de_tarefas)) == 0) // Tomara que funcione! peguei a ideia de:
            return true;                                                                                    // https://stackoverflow.com/questions/9120065/best-way-to-compare-two-int-arrays-of-the-same-length

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

bool ciclo_populacCao(populacCao* amostra, Cabecca_Matriz** mMatriz, int** auxiliar){ //IMPORTANTE VER COMO IMPLEMENTAR MUTAÇÃO!!!!

    if(amostra->qtde_de_individuo_ocupado >= amostra->qtde_de_individuo){ // Atingiu o limite! EXTERMINAR A POPULAÇÃO!!!
        printf(">>> População cheia! ciclo_populacCao abortado no início.\n");
        return false;
    }
    int ref = amostra->qtde_de_individuo_ocupado;

    individuo** novos = cruzamento(roleta_vida(amostra), roleta_vida(amostra), (*mMatriz)->total_de_tarefa); // NÃO FUNCIONA
    assert(novos != NULL);                                                                                 /// FUNCIONA
    novos[0]->fitness = makespan_de_uma_sequencia(novos[0]->genes, auxiliar, mMatriz);                       // NÃO FUNCIONA
    //assert(novos[0].genes != NULL);                                                                       /// FUNCIONA
    novos[1]->fitness = makespan_de_uma_sequencia(novos[1]->genes, auxiliar, mMatriz);                       // NÃO FUNCIONA
    //assert(novos[1].genes != NULL);
                                                                       ///FUNCIONA
    if(!insere_na_populacCao(amostra, novos[0])){
        return false;
        printf("entrei aqui");
    } // Atingiu o limite! EXTERMINAR A POPULAÇÃO!!!

    if(!insere_na_populacCao(amostra, novos[1])) // Atingiu o limite! EXTERMINAR A POPULAÇÃO!!!
        return false;

    if(amostra->qtde_de_individuo_ocupado > ref)                                                   /// pOR QUE RAIOS NÃO FUNCIONA????
        normaliza_porcentagem(amostra);                                                               /// PORQUE VOCÊ É CEGO!!!!!!!!!!!!!!!!!!!!!
                                                                                                    // ref >>>>>>>>>>>> amostra->qtde_de_individuo_ocupado
                                                                                                    /// NÃO (SÃO 22:07 e só vi isso agora...)
                                                                                                // ref <<<<<<<<<<<<<<<< amostra->qtde_de_individuo_ocupado
    return true;
}

void THANOS_tinha_razao(populacCao* amostra){ // Aqui comecei a duvidar do código
    int i;
    individuo* morto;
    for(i = amostra->qtde_de_individuo / 2; i < amostra->qtde_de_individuo; i++){
        morto = amostra->individuo[i];
        amostra->individuo[i] = NULL;
        mata_alguem(morto);
    }
    amostra->qtde_de_individuo_ocupado = amostra->qtde_de_individuo / 2;
}

void AO_JAIRO_COM_LOVE(populacCao* amostra){ // Aqui comecei a acreditar no código
    int i;
    individuo* pai_do_jairo;
    for(i = 0; i < amostra->qtde_de_individuo_ocupado; i++){
        pai_do_jairo = amostra->individuo[i];
        amostra->individuo[i] = NULL;
        mata_alguem(pai_do_jairo);
    }
    free(amostra->individuo);
    //free(amostra->darwin_boy);
}

bool ANDAR_COM_FE_VOU_POIS_NAO_COSTUMA_FAIAR(populacCao* amostra){  //Aqui sei lá... Só funciona...

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
