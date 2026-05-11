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

void init(SDL_Window **window, SDL_Renderer **renderer)
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    *window = SDL_CreateWindow("QCM Game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT, 0);

    *renderer = SDL_CreateRenderer(*window, -1, 0);
}

void loadQuestions(Question q[])
{
    strcpy(q[0].question, "Que signifie SDL ?");
    strcpy(q[0].reponses[0], "Simple DirectMedia Layer");
    strcpy(q[0].reponses[1], "System Design Library");
    strcpy(q[0].reponses[2], "Source Dynamic Link");
    q[0].bonne_reponse = 0;
    
    strcpy(q[1].question, "Quelle fonction initialise SDL ?");
    strcpy(q[1].reponses[0], "SDL_Start()");
    strcpy(q[1].reponses[1], "SDL_Init()");
    strcpy(q[1].reponses[2], "SDL_Open()");
    q[1].bonne_reponse = 1;
    
    strcpy(q[2].question, "Quelle bibliotheque charge les images ?");
    strcpy(q[2].reponses[0], "SDL_ttf");
    strcpy(q[2].reponses[1], "SDL_mixer");
    strcpy(q[2].reponses[2], "SDL_image");
    q[2].bonne_reponse = 2;
    
   strcpy(q[3].question, "Quelle fonction ferme SDL ?");
    strcpy(q[3].reponses[0], "SDL_Quit()");
    strcpy(q[3].reponses[1], "SDL_Close()");
    strcpy(q[3].reponses[2], "SDL_End()");
    q[3].bonne_reponse = 0;


   strcpy(q[4].question, "SDL_ttf sert a ?");
    strcpy(q[4].reponses[0], "Jouer musique");
    strcpy(q[4].reponses[1], "Afficher texte");
    strcpy(q[4].reponses[2], "Creer fenetre");
    q[4].bonne_reponse = 1;
}

SDL_Texture* loadTexture(char *path, SDL_Renderer *renderer)
{
    SDL_Surface *surface = IMG_Load(path);

    if (!surface)
    {
        printf("Erreur image %s : %s\n", path, IMG_GetError());
        return NULL;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture)
    {
        printf("Erreur texture : %s\n", SDL_GetError());
    }

    return texture;
}

void loadImages(SDL_Renderer *renderer, Image *bg, Image btn[])
{
    bg->texture = loadTexture("images/bg.png", renderer);
    bg->pos = (SDL_Rect){0,0,WIDTH,HEIGHT};

    for(int i=0;i<3;i++)
    {
        char path[50];
        sprintf(path, "images/btn%d.png", i+1);
        btn[i].texture = loadTexture(path, renderer);

        btn[i].pos.x = 250;
        btn[i].pos.y = 250 + i*100;
        btn[i].pos.w = 300;
        btn[i].pos.h = 60;
    }
}

void afficherTexte(SDL_Renderer *renderer, TTF_Font *font, char *txt, int x, int y)
{
    SDL_Color color = {255,255,255};
    SDL_Surface *s = TTF_RenderText_Blended(font, txt, color);
    SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, s);

    SDL_Rect pos = {x,y,s->w,s->h};
    SDL_RenderCopy(renderer, t, NULL, &pos);

    SDL_FreeSurface(s);
    SDL_DestroyTexture(t);
}

void afficher(SDL_Renderer *renderer, TTF_Font *font, Image bg, Image btn[], Question q, int score)
{
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, bg.texture, NULL, &bg.pos);

    char scoreText[50];
    sprintf(scoreText, "Score: %d", score);
    afficherTexte(renderer, font, scoreText, 20, 20);

    afficherTexte(renderer, font, q.question, 200, 100);

    for(int i=0;i<3;i++)
    {
        SDL_RenderCopy(renderer, btn[i].texture, NULL, &btn[i].pos);
        afficherTexte(renderer, font, q.reponses[i], btn[i].pos.x+20, btn[i].pos.y+15);
    }

    SDL_RenderPresent(renderer);
}

int handleMouse(SDL_Event event, Image btn[])
{
    if(event.type == SDL_MOUSEBUTTONDOWN)
    {
        int x = event.button.x;
        int y = event.button.y;

        for(int i=0;i<3;i++)
        {
            if(x >= btn[i].pos.x && x <= btn[i].pos.x + btn[i].pos.w &&
               y >= btn[i].pos.y && y <= btn[i].pos.y + btn[i].pos.h)
            {
                return i;
            }
        }
    }
    return -1;
}

void clean(SDL_Window *window, SDL_Renderer *renderer, Image bg, Image btn[])
{
    SDL_DestroyTexture(bg.texture);
    for(int i=0;i<3;i++)
        SDL_DestroyTexture(btn[i].texture);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}
