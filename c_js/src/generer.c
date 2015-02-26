/**
 * \file generer.c
 * \brief génération de la grille de jeu
 * \version 1.0
 * \date 23 mai 2012
 *
 * Programme de génération d'une grille de jeu et d'une liste de mots.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grille.h"



int main(int argc, char* argv[]){
    printf("Content-type:text/html\n\n");
    int x,y,n;
    char *pRequestMethod;
    char *msg;
    char inputBuffer[8];
    pRequestMethod = getenv("REQUEST_METHOD");
    //printf("%s#",pRequestMethod);
    if(strcmp(pRequestMethod,"GET")==0){
        msg=getenv("QUERY_STRING");
        if(msg!=NULL){
            strcpy(inputBuffer,msg);
            //printf("%s#",inputBuffer);
            char level = inputBuffer[6];//level=1/2/3
            //printf("%c",level);
            //Grille g;
            if(level=='1'){
                x=y=8;
                n=4;
            }
            else if(level=='2'){
                x=y=10;
                n=6;
            }
            else {
                x=y=15;
                n=8;
            }
        }
    }
    Grille g;
    while(!genererGrille(&g,x,y,n,"dict_e","ref_dict_e"));
    int i,j,k;
    for(i=0;i<x;i++){
        for(j=0;j<y;j++){
            printf("%c",g.tableau[i][j]);
        }
    }
    for(k=0;k<n;k++)printf("#%s",g.listeMots[k].mot);
    return EXIT_SUCCESS;
}
