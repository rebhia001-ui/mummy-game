/**
 * @file source.h
 * @brief Header des fonctions
 */#ifndef SOURCE_H
#define SOURCE_H

typedef struct {
    char question[200];
    char A[100];
    char B[100];
    char C[100];
    char reponse;
    int dejaVu;
} Enigme;

void charger(Enigme tab[], char nomFichier[]);
int randomQuestion(Enigme tab[]);

#endif
