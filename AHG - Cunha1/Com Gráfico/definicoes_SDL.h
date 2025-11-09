#ifndef DEFINICOES_SDL_H_INCLUDED
#define DEFINICOES_SDL_H_INCLUDED

#include "definicoes.h"

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>

typedef struct {
    SDL_Window* aWindow;
    SDL_Renderer* aRenderer;
    SDL_Texture* aTextura;
    SDL_Surface* aSurface;
    TTF_Font* aFonte;
    int largura;
    int altura;
} app_estado;

typedef struct ponto{
    SDL_FRect* Area;
    int fitness;
    struct ponto* prox;
    SDL_Color cor;
} indiv_SDL;

void ciclo_SDL(app_estado* novo, populacCao* amostra);
bool determinar_grafico_SDL(int sobre_o_que);

#endif // DEFINICOES_SDL_H_INCLUDED
