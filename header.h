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
#ifndef HEADER_H
#define HEADER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct {
    char question[100];
    char reponses[3][50];
    int bonne_reponse;
} Question;

typedef struct {
    SDL_Texture *texture;
    SDL_Rect pos;
} Image;

void init(SDL_Window **window, SDL_Renderer **renderer);
void loadQuestions(Question q[]);
void loadImages(SDL_Renderer *renderer, Image *bg, Image btn[]);
void afficher(SDL_Renderer *renderer, TTF_Font *font, Image bg, Image btn[], Question q, int score);
int handleMouse(SDL_Event event, Image btn[]);
void clean(SDL_Window *window, SDL_Renderer *renderer, Image bg, Image btn[]);

#endif
