#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "source.h"

void charger(Enigme tab[], char nomFichier[]) {
    FILE *f = fopen(nomFichier, "r");

    if(f == NULL) {
        printf("Erreur fichier\n");
        exit(1);
    }

    for(int i=0;i<10;i++) {
        fscanf(f, "Q: %[^\n]\n", tab[i].question);
        fscanf(f, "A: %[^\n]\n", tab[i].A);
        fscanf(f, "B: %[^\n]\n", tab[i].B);
        fscanf(f, "C: %[^\n]\n", tab[i].C);
        fscanf(f, "R: %c\n\n", &tab[i].reponse);

        tab[i].dejaVu = 0;
    }

    fclose(f);
}

int randomQuestion(Enigme tab[]) {
    int i;
    do {
        i = rand() % 10;
    } while(tab[i].dejaVu);

    tab[i].dejaVu = 1;
    return i;
}
