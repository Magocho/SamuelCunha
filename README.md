# SamuelCunha

## Descrição
> Se alguém já perdeu a loteria genética, certamente foi o SamuelCunha, pois:
>   1. Ajudei a progamar ele;
>   2. Ele nem genes tem.
>
> — *Eu conversando com Darwin, sobre a origem da idiotice e reprodução de algoritmos*

## O que é pr fazer
Criar um código 👍 

> *Por que?* -> Uhm, ***boa pergunta***.
>
> — *Qualquer aluno de BCC.*

## Esquema geral:
```text
AHG/
│
├─ flowshop1.txt               # Instâncias para se aplicar o Algoritmo Genético (AHG)
│
├─ código/(.c)
│   ├─ main.c                  # Ponto de entrada do programa (E junção de todas as outras funções).
│   ├─ makespan.c              # Criador de Matrizes (Máquinas x Tarefas) e calculador de Makespan.
│   ├─ cromossomo.c            # Cria indivíduos, define sua reprodução e mutação.
│   ├─ Roleta_vida.c           # Gerencia um conjunto de indivíduos, também ordena e decide quem deve reproduzir.
│   ├─ leitor_txt.c            # Leitor do arquivo .txt e informações do usuário.
│   ├─ debug.c                 # Para testes específico e ver onde deu ruim.
|   └─ SDL_gene.c (Opcional)   # Visualizador pseudo-gráfico/interativa/funcional de uma população.
│ 
└─ header/(.h)
    ├─ definicoes.h                 # Quais funções realmente se precisa.
    └─ definicoes_SDL.h (Opcional)  # Para tratar do gráfico.
```

### Pseudocódigo
```C
int SamuelCunha_AHG(int número_de_gerações, int tamanho_da_população){

    int geração = 0;
    População grupo = cria_pop_inicial(tamanho_da_população);

    ordenador_de_população(&grupo);

    while(geração < número_de_gerações){         // Pode-se melhorar aqui! (TALVEZ)
        if(grupo >= tamanho_da_população){      // Também, pode ser mais tolerante nesse if. (UM TALVEZ MAIOR)
            reduz_população_pela_metade(grupo);
            geração++;
        }
        else reprodução(grupo);
    }

    return grupo->melhor_encontrado;
}
```

## O que falta fazer?

- ~~FUNCIONAR~~ [x]

    > isso SEMPRE funcionou sim, *ink ink*

- Discutir a MUTAÇÃO (*Queremos mutação?*) []

    - SIM

        > Ficará mais *geneticamente heurístico* o algoritmo e a função já está pronta.

    - NÃO 
        
        > É menos trabalhoso e não teremos nenhuma *surpresa* no meio do caminho.

- Definir um plano de população melhor que []

    > "O poder da população é **imensuravelmente** superior ao da memória heap." (de outra forma) Mi chegou a DeZ, morri tode mundE agora.
    >
    > — *Malthus, quando inquerido do preço do coco em Ubatuba*

    - Não tenho nenhuma sugestão...

- Implementar algumas funções para escrita em .txt que permita exportar para *excel* []

    > Para quê isso? Só anotar no papel e calcular o desvio padrão na mão! No BR basta colocar 19 alunos em um sala...
    >
    > Em 5% dos casos todos morrem, 30% dão a resposta errada e em 65% perdemos 10, mas temos um quase certo! (Só colocar 0 no final, eles esquecem a vírgula).

## O que pode melhorar?

> Não significa que será melhorado... É mais um passeio intelectual delirante (principalmente a parte *intelectual* do passeio).

- ~~O CÓDIGO INTEIRO... Por que não escrevi isso em Python?~~

- Tipo de dado da população

    - Utilizar unsigned long long talvez? (Passeie comigo por um momento)

          Um int (que se usa no momento) ocupa no momento 4 byte — em uma arquitetura de 64 sim, sim...

            Logo, se uma sequência ocupar por exemplo 4 tarefas, precisamos de 4 int que seria 4 * 16 = 64 bit ótimo!

            Mas, se representáarmos ela por bit? 

            Bem (uma péssima solução, pois delirei isso 08/11 às 23h) podemos fazer uma matriz:

                pos   1 2 3 4 Tarefa
        
                (1)   0 0 0 1 -> Tarefa [4] está em 1
        
                (2)   0 0 1 0 -> Tarefa [3] está em 3
        
                (3)   0 1 0 0 -> Tarefa [2] está em 2
        
                (4)   1 0 0 0 -> Tarefa [1] está em 4 -- Assim: 4321 (seria esse número na sequência)

            Com isso podemos gerar todas as combinações, assim qual o tamanho que ocupa? 16 bit!

            Isso é, 1/4 do tamanho em bit do int.

            SE, (grande se esse) assumirmos que é sempre verdade a viagem acima, podemos dizer que:

            Quando for para N em int, sua representação em bit será N/4. De forma grossa, poderimas ter uma população 4 vezes maior!
        
        Observações (Na verdade problemas mesmo dessa ideia)

        1. A quantidade de operações seria *possivelmente* maior (Tenho quase certeza disso)
            
            1. E também, sua progamação é mais trabalhosa e difícil que a de ints

        2. O aumento **real** da população haverá de ser descoberta na prática, pois talvez ocorra alguma limitação que desconheço.

        3. TALVEZ (grande talvez esse) nem sempre em AHG:
            
            > MAIOR POPULAÇÃO == MELHOR RESULTADO (OU MESMO CHANCE DE UM)

- Talvez, um *hashtable*? (Sempre uma opção)


P.S. Markdown é uma linguagem bem divertida para se escrever qualquer coisa...