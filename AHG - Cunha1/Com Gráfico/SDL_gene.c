#include "definicoes_SDL.h"
/*
    Aqui fica a parte gráfica e sua lógica.
    P.S. Não funciona muito bem E NÃO ESTÁ INCORPORADA NO DEBUG.C
*/
SDL_Color AMARELOsdl = {255, 255, 0, 255};
SDL_Color PRETOsdl = {0, 0, 0, 255};
SDL_Color VERM_ESCsdl = {200, 30, 30, 255};
void inicio_SDL(){
	assert(SDL_Init(SDL_INIT_VIDEO));
    TTF_Init();
}

bool cria_tela_SDL(app_estado* atual, int largura, int altura){

	atual->aWindow = SDL_CreateWindow("AHG-CA", largura, altura, SDL_WINDOW_RESIZABLE);
    atual->aFonte = TTF_OpenFont("LiberationMono-Regular.ttf", 24.0f);
    atual->aRenderer = SDL_CreateRenderer(atual->aWindow, NULL);

    atual->aSurface = IMG_Load("Imagem/darwin.png");
    SDL_SetWindowIcon(atual->aWindow, atual->aSurface);
    SDL_DestroySurface(atual->aSurface);

    atual->largura = largura;
    atual->altura = altura;

	return true;
}

void termina_SDL(app_estado* atual){

    SDL_DestroyRenderer(atual->aRenderer);
    SDL_DestroyWindow(atual->aWindow);
    SDL_DestroyTexture(atual->aTextura);
    SDL_DestroySurface(atual->aSurface);
    TTF_CloseFont(atual->aFonte);
    TTF_Quit();
    SDL_Quit();
}

void cria_membro_fila(indiv_SDL** fila){

    indiv_SDL* novo = malloc(sizeof(indiv_SDL));
    assert(novo != NULL);

    novo->Area = malloc(sizeof(SDL_FRect));
    memset(novo->Area, 0, sizeof(SDL_FRect));
    novo->cor = VERM_ESCsdl;
    novo->prox = NULL;

    if(*fila == NULL){
        *fila = novo;
    }
    else{
        indiv_SDL* ref = *fila;
        while(ref->prox != NULL)
            ref = ref->prox;
        ref->prox = novo;
    }
}

float aloca_espaco_individuo(populacCao* amostra, indiv_SDL** fila){

    individuo** ref = amostra->individuo;
    indiv_SDL* atual = NULL;
    int i;
    float total = 0.0;
    float acumulador_x = 0.0;

    for(i = 0; i < amostra->qtde_de_individuo_ocupado; i++){

        total += ref[i]->porcentagem;
        if(i == 0){
            cria_membro_fila(fila);
            atual = *fila;
            atual->fitness = ref[i]->fitness;
            atual->Area->h = 1;
            atual->Area->x = 0;
            atual->Area->w = ref[i]->porcentagem;
            acumulador_x += ref[i]->porcentagem;
            atual->Area->y = 1;
        }
        else{
            if(ref[i]->fitness == atual->fitness){
                atual->Area->h += 1;
                atual->Area->w  += ref[i]->porcentagem;
                acumulador_x += ref[i]->porcentagem;
            }
            else{
                cria_membro_fila(fila);
                atual = atual->prox;
                atual->fitness = ref[i]->fitness;
                atual->Area->h = 1;
                atual->Area->y = 1;
                atual->Area->x = acumulador_x;
                atual->Area->w = ref[i]->porcentagem;
                acumulador_x += ref[i]->porcentagem;
            }
        }
    }
    return total;
}

void redimensiona_UM(app_estado* atual, SDL_FRect* antigo, SDL_FRect* auxiliar, float total){

    float margem_x = atual->largura / 12.0f;
    float base_y = atual->altura - atual->altura / 4.0f;
    float largura_util =  atual->largura - 2 * margem_x;

    auxiliar->x = margem_x + (antigo->x / total) * largura_util;
    auxiliar->w = (antigo->w / total) * largura_util;

    auxiliar->h = (antigo->h * atual->altura) / 30.0f;
    auxiliar->y = base_y - auxiliar->h;
}

void desenha_texto(app_estado* atual, const char* texto, SDL_Color cor, float x, float y){

    atual->aSurface = TTF_RenderText_Blended(atual->aFonte, texto, 0, cor);

    atual->aTextura = SDL_CreateTextureFromSurface(atual->aRenderer, atual->aSurface);

    SDL_FRect destRect;
    SDL_GetTextureSize(atual->aTextura , &destRect.w, &destRect.h);
    destRect.x = x;
    destRect.y = y;

    SDL_RenderTexture(atual->aRenderer, atual->aTextura, NULL, &destRect);

    SDL_DestroyTexture(atual->aTextura);
    SDL_DestroySurface(atual->aSurface);
}


void desenha_grafico(app_estado* atual, indiv_SDL* fila, float soma){

    SDL_SetRenderDrawColor(atual->aRenderer, 0, 0, 0, 255);

    SDL_RenderLine(atual->aRenderer, (atual->largura / 12), (atual->altura - atual->altura / 4), (atual->largura - atual->largura / 12), (atual->altura - atual->altura / 4));
    SDL_RenderLine(atual->aRenderer, (atual->largura / 12), (atual->altura - atual->altura / 4), (atual->largura / 12), (atual->altura / 16));

    indiv_SDL* ref = fila;
    SDL_FRect auxiliar;

    int i;
    int centralizar = TTF_GetFontHeight(atual->aFonte);
    float y;
    char enunciado[6];
    for(i = 1; i < 21; i++){
        snprintf(enunciado, 6, "%d", i);
        y = (atual->altura - atual->altura / 4.0f) - ((i * atual->altura) / 30.0f);
        y -= centralizar / 2.0f;
        desenha_texto(atual, enunciado, PRETOsdl, ((atual->largura / 12) - (atual->largura / 48)), y);
    }

    for(ref = fila; ref != NULL; ref = ref->prox){
        redimensiona_UM(atual, ref->Area, &auxiliar, soma);

        SDL_SetRenderDrawColor(atual->aRenderer, ref->cor.r, ref->cor.g, ref->cor.b, ref->cor.a);
        SDL_RenderFillRect(atual->aRenderer, &auxiliar);

        SDL_SetRenderDrawColor(atual->aRenderer, 0, 0, 0, 255);
        SDL_RenderRect(atual->aRenderer, &auxiliar);
    }
}

void deixa_vermelho(app_estado* atual, indiv_SDL* fila){
    indiv_SDL* ref;

    for(ref = fila; ref != NULL; ref = ref->prox){
        if(ref->cor.r == AMARELOsdl.r && ref->cor.g == AMARELOsdl.g && ref->cor.b == AMARELOsdl.b && ref->cor.a == AMARELOsdl.a){
            ref->cor = VERM_ESCsdl;
            return;
        }
    }
}

bool tocou_na_caixa(float x, float y, app_estado* atual, indiv_SDL* fila, int* makespaN, float soma){
    indiv_SDL* ref;
    SDL_FRect auxiliar;

    for(ref = fila; ref != NULL; ref = ref->prox){
        redimensiona_UM(atual, ref->Area, &auxiliar, soma);

        if(x > auxiliar.x && x < (auxiliar.x + auxiliar.w) && y > auxiliar.y && y < (auxiliar.y + auxiliar.h)){
            *makespaN = ref->fitness;
            ref->cor = AMARELOsdl;
            return true;
        }
    }
    return false;
}

void imprime_DNA_individuo(populacCao* Amostra, app_estado* atual, float x, float y, int makespaN){
    int i, j;
    float altura = y;
    individuo** ref = Amostra->individuo;
    char enunciado[512];
    char temp[10];
    TTF_Font* fonte = atual->aFonte;

    if(Amostra->qtde_de_tarefas > 70)
        atual->aFonte = TTF_OpenFont("LiberationMono-Regular.ttf", 7.4);
    else atual->aFonte = TTF_OpenFont("LiberationMono-Regular.ttf", 10.4);

    for(i = 0; i < Amostra->qtde_de_individuo_ocupado; i++){
        if(ref[i]->fitness == makespaN){
            enunciado[0] = '\0';
            for(j = 0; j < Amostra->qtde_de_tarefas; j++){
                snprintf(temp, sizeof(temp), "| %d ", ref[i]->genes[j]);
                strcat(enunciado, temp);
            }
            strcat(enunciado, "|");
            desenha_texto(atual, enunciado, PRETOsdl, x, altura);
            altura += 11.0f;
        }
    }
    TTF_CloseFont(atual->aFonte);
    atual->aFonte = fonte;
}

void libera_fila_SDL(indiv_SDL* fila){
    indiv_SDL* atual = fila;
    indiv_SDL* prox;

    while(atual != NULL){
        prox = atual->prox;

        if(atual->Area != NULL)
            free(atual->Area);

        free(atual);
        atual = prox;
    }
}

void loop_SDL(app_estado* atual, populacCao* Amostra){

    char enunciado[51];
    int makespaN = 0;
    bool quit = false;
    bool texto = false;

    indiv_SDL* fila = NULL;

    SDL_Event evento;
    SDL_zero(evento);

    int largura_nova = 0;
    int altura_nova = 0;
    float x, y;

    float total_porcentagem = aloca_espaco_individuo(Amostra, &fila);

    const int FPS = 60;
    const float FRAME_TIME_MS = 1000.0f / FPS;

    while(!quit){

        Uint64 start_ns = SDL_GetTicksNS();

        while(SDL_PollEvent(&evento)){
            switch(evento.type){
                case SDL_EVENT_QUIT:
                    quit = true;
                    break;
                case SDL_EVENT_WINDOW_RESIZED:
                    largura_nova = evento.window.data1;
                    altura_nova = evento.window.data2;
                    atual->altura = altura_nova;
                    atual->largura = largura_nova;
                    break;
                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                    x = evento.button.x;
                    y = evento.button.y;
                    if(texto)
                        deixa_vermelho(atual, fila);
                    if(tocou_na_caixa(x, y, atual, fila, &makespaN, total_porcentagem))
                        texto = true;
                    break;
                case SDL_EVENT_KEY_DOWN:
                    if(evento.key.key == SDLK_ESCAPE)
                        quit = true;
                    break;
                default:
                    break;
            }
        }

        SDL_SetRenderDrawColor(atual->aRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(atual->aRenderer);
        desenha_grafico(atual, fila, total_porcentagem);

        desenha_texto(atual, "0%", PRETOsdl, (atual->largura / 12), (atual->altura - atual->altura / 4) + 25);
        desenha_texto(atual, "50%", PRETOsdl, (atual->largura - atual->largura / 12)/2 , (atual->altura - atual->altura / 4) + 25);
        desenha_texto(atual, "100%", PRETOsdl, (atual->largura - atual->largura / 12) , (atual->altura - atual->altura / 4) + 25);

        if(texto){
            snprintf(enunciado, 51, "(MAKESPAN): %d", makespaN);
            desenha_texto(atual, "FITNESS", PRETOsdl, (atual->largura / 64) , (atual->altura - atual->altura / 8));
            desenha_texto(atual, enunciado, PRETOsdl, (atual->largura / 64) , (atual->altura - atual->altura / 10));
            imprime_DNA_individuo(Amostra, atual, 2*(atual->largura / 14) ,(atual->altura - atual->altura / 4) + 50, makespaN);
        }

        SDL_RenderPresent(atual->aRenderer);

        Uint64 end_ns = SDL_GetTicksNS();
        float elapsed_ms = (end_ns - start_ns) / 1e6f;

        if(elapsed_ms < FRAME_TIME_MS)
            SDL_Delay((Uint32)(FRAME_TIME_MS - elapsed_ms));
    }

    libera_fila_SDL(fila);
}

void ciclo_SDL(app_estado* novo, populacCao* amostra){
    inicio_SDL();
    assert(cria_tela_SDL(novo, 960, 640));
    loop_SDL(novo, amostra);
    termina_SDL(novo);
}

bool determinar_grafico_SDL(int sobre_o_que){
    char resp = 'a';

    printf(CINZA);
    switch(sobre_o_que){
    case 1:
        printf("\n\t> "ROXO"[SDL3]"CINZA" Deseja o grafico da pop. inicial?["VERDE"S"CINZA"/"VERMELHO"N"CINZA"]\n\t> "VERDE);
        break;
    case 2:
        printf("\n\t> "ROXO"[SDL3]"CINZA" Deseja o grafico da pop. entre as geracoes?["VERDE"S"CINZA"/"VERMELHO"N"CINZA"]\n\t> "VERDE);
        break;
    case 3:
        printf("\n\t> "ROXO"[SDL3]"CINZA" Deseja o grafico da pop. final?["VERDE"S"CINZA"/"VERMELHO"N"CINZA"]\n\t> "VERDE);
        break;
    default:
        printf(CINZA);
        return false;

    }

    while(resp != 'N' && resp != 'n' && resp != 's' && resp != 'S'){
        if(scanf(" %c", &resp) == 1 && resp != 'N' && resp != 'n' && resp != 's' && resp != 'S'){
            printf(VERMELHO"\t> ERRO: insira uma resposta valida!\n"CINZA"\t> "VERDE);
            getchar();
        }
    }

    printf(CINZA);
    if(resp == 's' || resp == 'S')
            return true;

    return false;
}
