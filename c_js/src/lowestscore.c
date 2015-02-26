/**
 * \file lowestscore.c
 * \brief Programme pour afficher le score le plus bas
 * \version 1.0
 * \date 23 mai 2012
 *
 * Programme pour afficher le score le plus bas
 *
 */



#include <string.h>
#include <stdlib.h>
#include "score.h"

int main(){
    printf("Content-type:text/html\n\n");
    FILE *f = NULL;
    lowestScore(f);
    return EXIT_SUCCESS;
}
