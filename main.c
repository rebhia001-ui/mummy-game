/**
 * @file main.c
 * @brief programme principal du jeu
 * @author Zeineb
 * @version 1.0
 * @date 2026
 *
 * Testing program for background scrollilng 
 *  
 */ 
#include "header.h"

int main()
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

    Question q[5];
    Image bg;
    Image btn[3];

    int score = 0;
    int current = 0;
    int running = 1;

    init(&window, &renderer);
    loadQuestions(q);
    loadImages(renderer, &bg, btn);

    TTF_Font *font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 24);

if(!font)
{
    printf("Erreur font: %s\n", TTF_GetError());
    return 1;
}

    while(running)
    {
        afficher(renderer, font, bg, btn, q[current], score);

        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                running = 0;

            int choix = handleMouse(event, btn);

            if(choix != -1)
            {
                if(choix == q[current].bonne_reponse)
                    score += 5;
                else
                    score -= 5;

                current++;

                if(current >= 5)
                {
                    printf("Score final: %d\n", score);
                    running = 0;
                }

                SDL_Delay(300);
            }
        }
    }

    clean(window, renderer, bg, btn);
    return 0;
}
