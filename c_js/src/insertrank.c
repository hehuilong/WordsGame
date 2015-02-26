/**
 * \file insertrank.c
 * \brief Programme d'insertion d'un nom dans la liste des scores.
 * \version 1.0
 * \date 23 mai 2012
 *
 * Programme pour ajouter un nom dans la liste des scores
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grille.h"
#include "score.h"

int main(int argc, char* argv[]){
    setvbuf(stdin,NULL,_IONBF,0);     /*close stdin buffer*/
    printf("Content-type:text/html\n\n");
    char *pRequestMethod;
    char nom[TAILLE_MAX];
    int score;
    char inputBuffer[TAILLE_MAX+10];
    pRequestMethod = getenv("REQUEST_METHOD");
    if(strcmp(pRequestMethod,"POST")==0){
        fgets(inputBuffer,TAILLE_MAX+10,stdin);
        sscanf(inputBuffer, "%s : %d", nom, &score);
        if(strlen(nom)>TAILLE_MAX-1||strlen(nom)==0){
            return EXIT_SUCCESS;
        }
        FILE * f=NULL;
        ajouterScore(f, nom, score);
    }

    return EXIT_SUCCESS;
}

