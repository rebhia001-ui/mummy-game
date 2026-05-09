/**
 * @file main.c
 * @brief Programme principal du jeu
 * @author Ahmed
 * @version 1.0
 * @date 2026
 */#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "source.h"

void afficherTexte(SDL_Renderer *renderer, TTF_Font *font, char *text, int x, int y) {
    SDL_Color color = {255,255,255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect = {x,y,surface->w,surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

int main() {

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);

    SDL_Window *window = SDL_CreateWindow("Quiz",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,600,0);

    SDL_Renderer *renderer = SDL_CreateRenderer(window,-1,0);

    TTF_Font *font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf", 28);

    // 🔥 BACKGROUND LOAD
    SDL_Surface *bgSurface = IMG_Load("background.png");
    if(bgSurface == NULL) {
        printf("Erreur chargement background\n");
        return 1;
    }
    SDL_Texture *bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);

    Enigme tab[10];

    srand(time(NULL));

    int score = 0;
    int vies = 3;
    int niveau = 0;
    int questionsPosees = 0;

    Uint32 startTime = 0;
    int i = 0;

    SDL_Rect btnA = {50,150,400,40};
    SDL_Rect btnB = {50,200,400,40};
    SDL_Rect btnC = {50,250,400,40};

    int running = 1;
    SDL_Event e;

    while(running) {

        while(SDL_PollEvent(&e)) {

            if(e.type == SDL_QUIT)
                running = 0;

            if(e.type == SDL_KEYDOWN) {

                if(e.key.keysym.sym == SDLK_1) {
                    charger(tab,"questions_facile.txt");
                    for(int k=0;k<10;k++) tab[k].dejaVu = 0;

                    niveau = 1;
                    score = 0;
                    vies = 3;
                    questionsPosees = 0;

                    i = randomQuestion(tab);
                    startTime = SDL_GetTicks();
                }

                if(e.key.keysym.sym == SDLK_2) {
                    charger(tab,"questions_moyen.txt");
                    for(int k=0;k<10;k++) tab[k].dejaVu = 0;

                    niveau = 2;
                    score = 0;
                    vies = 3;
                    questionsPosees = 0;

                    i = randomQuestion(tab);
                    startTime = SDL_GetTicks();
                }

                if(e.key.keysym.sym == SDLK_3) {
                    charger(tab,"questions_difficile.txt");
                    for(int k=0;k<10;k++) tab[k].dejaVu = 0;

                    niveau = 3;
                    score = 0;
                    vies = 3;
                    questionsPosees = 0;

                    i = randomQuestion(tab);
                    startTime = SDL_GetTicks();
                }

                if(e.key.keysym.sym == SDLK_0)
                    running = 0;
            }

            if(e.type == SDL_MOUSEBUTTONDOWN && niveau != 0 && vies > 0 && questionsPosees < 10) {

                int x = e.button.x;
                int y = e.button.y;

                char choix = 0;

                if(x > btnA.x && x < btnA.x+btnA.w &&
                   y > btnA.y && y < btnA.y+btnA.h)
                    choix = 'A';

                if(x > btnB.x && x < btnB.x+btnB.w &&
                   y > btnB.y && y < btnB.y+btnB.h)
                    choix = 'B';

                if(x > btnC.x && x < btnC.x+btnC.w &&
                   y > btnC.y && y < btnC.y+btnC.h)
                    choix = 'C';

                if(choix) {
                    if(choix == tab[i].reponse)
                        score++;
                    else
                        vies--;

                    questionsPosees++;

                    if(questionsPosees < 10)
                        i = randomQuestion(tab);

                    startTime = SDL_GetTicks();
                }
            }
        }

        // 🔥 BACKGROUND FULLSCREEN + SCALE
        int w, h;
        SDL_GetRendererOutputSize(renderer, &w, &h);

        int imgW, imgH;
        SDL_QueryTexture(bgTexture, NULL, NULL, &imgW, &imgH);

        float scaleX = (float)w / imgW;
        float scaleY = (float)h / imgH;
        float scale = (scaleX > scaleY) ? scaleX : scaleY;

        int newW = imgW * scale;
        int newH = imgH * scale;

        SDL_Rect bgRect;
        bgRect.w = newW;
        bgRect.h = newH;
        bgRect.x = (w - newW) / 2;
        bgRect.y = (h - newH) / 2;

        SDL_RenderCopy(renderer, bgTexture, NULL, &bgRect);

        if(niveau == 0) {
            afficherTexte(renderer,font,"1: Facile",300,200);
            afficherTexte(renderer,font,"2: Moyen",300,250);
            afficherTexte(renderer,font,"3: Difficile",300,300);
            afficherTexte(renderer,font,"0: Quitter",300,350);
        }

        if(niveau != 0 && vies > 0 && questionsPosees < 10) {

            afficherTexte(renderer,font,tab[i].question,50,50);
            afficherTexte(renderer,font,tab[i].A,50,150);
            afficherTexte(renderer,font,tab[i].B,50,200);
            afficherTexte(renderer,font,tab[i].C,50,250);

            char info[100];
            sprintf(info,"Score: %d | Vies: %d",score,vies);
            afficherTexte(renderer,font,info,50,350);

            Uint32 current = SDL_GetTicks();
            int seconds = (current - startTime) / 1000;

            char chrono[50];
            sprintf(chrono,"Temps: %d s",seconds);
            afficherTexte(renderer,font,chrono,50,400);

            if(seconds >= 10) {
                vies--;
                questionsPosees++;

                if(questionsPosees < 10)
                    i = randomQuestion(tab);

                startTime = SDL_GetTicks();
            }

            SDL_SetRenderDrawColor(renderer, 255,0,0,255);
            SDL_RenderDrawRect(renderer, &btnA);

            SDL_SetRenderDrawColor(renderer, 0,255,0,255);
            SDL_RenderDrawRect(renderer, &btnB);

            SDL_SetRenderDrawColor(renderer, 0,0,255,255);
            SDL_RenderDrawRect(renderer, &btnC);
        }

        if(vies <= 0 || questionsPosees >= 10) {
            char fin[100];
            sprintf(fin,"FIN! Score: %d/10",score);
            afficherTexte(renderer,font,fin,250,250);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(30);
    }

    SDL_DestroyTexture(bgTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}
